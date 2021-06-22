#pragma once
#include "Character/Player.h"
#include "Arena.h"

int Player::m_count = 0;


int Player::getCount()
{
    return m_count;
}

Player::Player(const sf::Vector2f& location , CharacterType character)
	: Character(location, character), m_playerNum(m_count)//, m_manaAndHealth(character)
{
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
        return;
    m_action = getActionFromKey(arena);

    Character::move(deltaTime, arena);
    m_manaAndHealth.move(); //move the health and mana bars
}

const sf::Vector2f* Player::getLocation() const
{
    return &(m_picture.getPosition());
}

Action Player::getActionFromKey(Arena& arena) //auto vecOfPAirs = {{}}
{
    //static Effect fireEffect{ (int)AttackType::FireDynamic },
    //              freezingEffect{ (int)AttackType::IceDynamic },
    //              explosionEffect{ (int)AttackType::FireStatic };

    static const
       std::initializer_list<std::initializer_list<std::pair<sf::Keyboard::Key, Action>>>
        keyToVectorMapping =
    { 
        {
        { sf::Keyboard::Right, Action { ActionType::Walking, Direction::Right } },
        { sf::Keyboard::Left , Action { ActionType::Walking, Direction::Left } },
        { sf::Keyboard::Up   , Action { ActionType::Walking, Direction::Up } },
        { sf::Keyboard::Down , Action { ActionType::Walking, Direction::Down } },
        { sf::Keyboard::Z    , Action { ActionType::Punching, Direction::Stay } },
        { sf::Keyboard::X    , Action { ActionType::SpecialDynamic, Direction::Stay } },
        { sf::Keyboard::C    , Action { ActionType::SpecialStatic, Direction::Stay } },
        { sf::Keyboard::Space, Action { ActionType::Sprinting, Direction::Stay } }
      },
      {
        { sf::Keyboard::L    , Action { ActionType::Walking, Direction::Right } },
        { sf::Keyboard::J    , Action { ActionType::Walking, Direction::Left } },
        { sf::Keyboard::I    , Action { ActionType::Walking, Direction::Up } },
        { sf::Keyboard::K    , Action { ActionType::Walking, Direction::Down } },
        { sf::Keyboard::R    , Action { ActionType::Punching, Direction::Stay } },
        { sf::Keyboard::T    , Action { ActionType::SpecialDynamic, Direction::Stay } },
        { sf::Keyboard::Y    , Action { ActionType::SpecialStatic, Direction::Stay } },
        { sf::Keyboard::H    , Action { ActionType::Sprinting, Direction::Stay } }
      }
    };
    //auto playerNumMap = keyToVectorMapping.at(m_playerNum)
    int i = 0;
    for (const auto& playerMap : keyToVectorMapping)
    {
        if (i == m_playerNum) //use the keys according to the player number
        {
            for (const auto& pair : playerMap)
            {
                AttackType attackType;  // for special attacks

                if (sf::Keyboard::isKeyPressed(pair.first))
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
                    default:
                        m_speed = SPEED; //change to regular speed
                        break;
                    }

                    return pair.second;
                }
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

