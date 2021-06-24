#pragma once
#include "Character/Player.h"
#include "Arena.h"

int Player::m_count = 0;


int Player::getCount()
{
    return m_count;
}

int Player::getPlayerNum() const
{
    return m_playerNum;
}

void Player::resetCount()
{
    m_count = 0;
}

Player::Player(const sf::Vector2f& location , CharacterType character, bool isPuppet)
	: Character(location, character), m_playerNum(m_count), m_puppet(isPuppet)
{
    if (m_playerNum)
        m_picture.setPosition(location.x, location.y + VERTICAL_OFFSET);
    m_specialAttacks = character == CharacterType::Alex ?
        std::make_pair(AttackType::FireDynamic, AttackType::FireStatic) : 
        std::make_pair(AttackType::IceDynamic, AttackType::IceStatic);

    m_manaAndHealth.setIcon(character);
    m_manaAndHealth.setLocation(m_playerNum);
    
    ++m_count;
}

void Player::move(const sf::Time& deltaTime, Arena& arena)
{
    if (inDisabledState(deltaTime))
    {
        //if (!m_puppet && arena.getMode() != Mode::Offline) //if in online mode and not a puppet
        //    sending(m_action);
        return;
    }
    m_action = getActionFromKey(arena);
    //if (!m_puppet && arena.getMode() != Mode::Offline) //if in online mode and not a puppet
    //    sending(m_action);
    Character::move(deltaTime, arena);
    m_manaAndHealth.move(); //move the health and mana bars
}

void Player::update(const sf::Time& deltaTime)
{
    //if (!m_puppet && Arena::getMode() != Mode::Offline) //if in online mode and not a puppet
    //{
    //    sending(m_action);
    //}
    //if (m_puppet)
    //{
    //    m_action = receive<Action>();
    //}

    Character::update(deltaTime);
}

const sf::Vector2f* Player::getLocation() const
{
    return &(m_picture.getPosition());
}

Action Player::getActionFromKey(Arena& arena) //auto vecOfPAirs = {{}}
{
    sf::Keyboard::Key keyPressed = DEFAULT_KEY;
    if (m_puppet && arena.getMode() != Mode::Offline) //if online and a puppet
    {
        keyPressed = receive<sf::Keyboard::Key>();
    }

    static const
       std::initializer_list<std::initializer_list<std::pair<sf::Keyboard::Key, Action>>>
        keyToVectorMapping =
    { 
        {
        { sf::Keyboard::Right, Action { ActionType::Walking, Direction::Right } },
        { sf::Keyboard::Left , Action { ActionType::Walking, Direction::Left } },
        { sf::Keyboard::Up   , Action { ActionType::Walking, Direction::Up } },
        { sf::Keyboard::Down , Action { ActionType::Walking, Direction::Down } },
        { sf::Keyboard::I    , Action { ActionType::Punching, Direction::Stay } },
        { sf::Keyboard::O    , Action { ActionType::SpecialDynamic, Direction::Stay } },
        { sf::Keyboard::P    , Action { ActionType::SpecialStatic, Direction::Stay } },
        { sf::Keyboard::RShift, Action { ActionType::Sprinting, Direction::Stay } },
        { DEFAULT_KEY, Action { ActionType::Standing, Direction::Stay } }
      },
      {
        { sf::Keyboard::D    , Action { ActionType::Walking, Direction::Right } },
        { sf::Keyboard::A    , Action { ActionType::Walking, Direction::Left } },
        { sf::Keyboard::W    , Action { ActionType::Walking, Direction::Up } },
        { sf::Keyboard::S    , Action { ActionType::Walking, Direction::Down } },
        { sf::Keyboard::C    , Action { ActionType::Punching, Direction::Stay } },
        { sf::Keyboard::V    , Action { ActionType::SpecialDynamic, Direction::Stay } },
        { sf::Keyboard::B    , Action { ActionType::SpecialStatic, Direction::Stay } },
        { sf::Keyboard::Space    , Action { ActionType::Sprinting, Direction::Stay } },
        { DEFAULT_KEY, Action { ActionType::Standing, Direction::Stay } }
      }
    };
    //auto playerNumMap = keyToVectorMapping.at(m_playerNum)
    int i = 0;
    for (const auto& playerMap : keyToVectorMapping)
    {
        if (i == m_playerNum || arena.getMode() != Mode::Offline) //use the keys according to the player number
        {
            for (const auto& pair : playerMap)
            {
                AttackType attackType;  // for special attacks

                if (!m_puppet && arena.getMode() != Mode::Offline && sf::Keyboard::isKeyPressed(pair.first)) //if in online mode and not a puppet
                    sending(pair.first);

                if (sf::Keyboard::isKeyPressed(pair.first) || (m_puppet && keyPressed == pair.first))
                {
                    switch (auto type = pair.second.first)
                    {
                    case ActionType::Sprinting:
                        m_speed = RUN_SPEED;
                        //pair.second.second = getFacingDirection();
                        return Action{ pair.second.first,getFacingDirection() };
                        break;
                    case ActionType::SpecialDynamic:
                        //m_manaAndHealth.decreaseMana(10);
                        // continue to fall through to static
                    case ActionType::SpecialStatic:
                        attackType = type == ActionType::SpecialDynamic ? m_specialAttacks.first : m_specialAttacks.second;
                        if (enoughMana(type) && m_specialAttackClock.getElapsedTime() > SPECIAL_DELAY)
                        {
                            m_specialAttackClock.restart();
                            arena.createSpecialAttack(type, attackType, this);
                            m_action.first = type;
                            m_manaAndHealth.decreaseMana(type);
                            m_disabled.restart();
                        }
                        else
                            //pair.second.first = ActionType::Standing;
                            return Action{ ActionType::Standing,pair.second.second };
                        break;
                    case ActionType::Punching:
                        if (m_punchingClock.getElapsedTime() > SPECIAL_DELAY && m_disabled.getElapsedTime().asSeconds() > PUNCHING_DELAY + 0.5f)
                        {
                            m_punchingClock.restart();
                            m_disabled.restart();
                        }
                        else
                            return Action{ ActionType::Standing,pair.second.second };
                        break;
                    default:
                        m_speed = SPEED; //change to regular speed
                        break;
                    }

                    return pair.second;
                }
            }
            if (!m_puppet && arena.getMode() != Mode::Offline)
            {
                sending(DEFAULT_KEY);
                return Action{ ActionType::Standing, Direction::Stay }; //default return
            }
        }
        i++;
    }

    return Action{ ActionType::Standing, Direction::Stay }; //default return
}

Player::~Player()
{
}

void Player::draw(sf::RenderWindow& window) const
{
    m_manaAndHealth.draw(window); //draw health and mana bars
    GameObject::draw(window);
}

