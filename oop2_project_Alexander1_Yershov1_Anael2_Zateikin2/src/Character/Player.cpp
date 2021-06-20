#pragma once
#include "Character/Player.h"
#include "Arena.h"

Player::Player(const sf::Vector2f& location , CharacterType character)
	: Character(location, character)
{
    m_specialAttacks = character == CharacterType::Alex ?
        std::make_pair(AttackType::FireDynamic, AttackType::FireStatic) : std::make_pair(AttackType::IceDynamic, AttackType::IceStatic);
}

void Player::move(const sf::Time& deltaTime, Arena& arena)
{
    if (inDisabledState(deltaTime))
        return;
    m_action = getActionFromKey(arena);

    Character::move(deltaTime, arena);
}

const sf::Vector2f* Player::getLocation() const
{
    return &(m_picture.getPosition());
}

Action Player::getActionFromKey(Arena& arena)
{
    /*if (inDisabledState(m_action.first, m_disabled.getElapsedTime()))
        return m_action;*/

    static const
        std::initializer_list<std::pair<sf::Keyboard::Key, Action>>
        keyToVectorMapping =
    {
        { sf::Keyboard::Right, Action { ActionType::Walking, Direction::Right } },
        { sf::Keyboard::Left , Action { ActionType::Walking, Direction::Left } },
        { sf::Keyboard::Up   , Action { ActionType::Walking, Direction::Up } },
        { sf::Keyboard::Down , Action { ActionType::Walking, Direction::Down } },
        { sf::Keyboard::Z    , Action { ActionType::Punching, Direction::Stay } },
        { sf::Keyboard::X    , Action { ActionType::SpecialDynamic, Direction::Stay } },
        { sf::Keyboard::C    , Action { ActionType::SpecialStatic, Direction::Stay } },
        { sf::Keyboard::Space, Action { ActionType::Sprinting, Direction::Stay } }

    };

    for (/*const*/ auto/*&*/ pair : keyToVectorMapping)
    {
        //m_speed = SPEED;
        AttackType attackType;  // for special attacks

        if (sf::Keyboard::isKeyPressed(pair.first))
        {
            switch (auto type = pair.second.first)
            {
            case ActionType::Sprinting:
                m_speed = RUN_SPEED;
                pair.second.second = getFacingDirection();
                break;
            case ActionType::SpecialDynamic:
                //m_mana -= 10;
                // continue to fall through to static
            case ActionType::SpecialStatic:
                attackType = type == ActionType::SpecialDynamic ? m_specialAttacks.first : m_specialAttacks.second;
                if (enoughMana(type) && m_specialAttackClock.getElapsedTime() > SPECIAL_DELAY)
                {
                    m_specialAttackClock.restart();
                    arena.createSpecialAttack(type, attackType, this);
                    m_action.first = type;
                    //m_mana -= 20;
                    m_disabled.restart();
                }
                else
                    pair.second.first = ActionType::Standing;
                break;
            default:
                m_speed = SPEED;
                break;
            }
            

            return pair.second;
        }
    }

    return Action{ ActionType::Standing, Direction::Stay };
}

Player::~Player()
{
}
