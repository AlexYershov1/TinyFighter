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
    m_action = getActionFromKey(arena);

    Character::move(deltaTime, arena);
}

const sf::Vector2f* Player::getLocation() const
{
    return &(m_picture.getPosition());
}

Action Player::getActionFromKey(Arena& arena)
{
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
        //{ sf::Keyboard::Space, Action { ActionType::Jumping, Direction::Stay } },
    };

    for (const auto& pair : keyToVectorMapping)
    {
        if (sf::Keyboard::isKeyPressed(pair.first))
        {
            // in case special attack is attempted
            auto type = pair.second.first;
            if (type == ActionType::SpecialDynamic )
            {
                if (enoughMana(ActionType::SpecialDynamic))
                {
                    arena.createSpecialAttack(type, m_specialAttacks.first, this);
                    m_action.first = ActionType::SpecialDynamic;
                    m_mana -= 30;
                }
                else
                {
                    m_action.first = ActionType::Standing;
                }
             }
            if (type == ActionType::SpecialStatic)
            {
                if (enoughMana(ActionType::SpecialStatic))
                {
                    arena.createSpecialAttack(type, m_specialAttacks.first, this);
                    m_action.first = ActionType::SpecialStatic;
                }
                else
                {
                    m_action.first = ActionType::Standing;
                }
            }
                
            return pair.second;
        }
    }

    return Action{ ActionType::Standing, Direction::Stay };
}

Player::~Player()
{
}