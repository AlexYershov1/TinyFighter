#pragma once
#include "MovingObject/Character/Player.h"

Player::Player(const sf::Vector2f& location , CharacterType character)
	: Character(location, character)
{
}

void Player::move(const sf::Time& deltaTime)
{
    m_action = getActionFromKey();
    Character::move(deltaTime);
}

const sf::Vector2f* Player::getLocation() const
{
    return &(m_picture.getPosition());
}

Action Player::getActionFromKey() const
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
        //{ sf::Keyboard::Space, Action { ActionType::Jumping, Direction::Stay } },
    };

    for (const auto& pair : keyToVectorMapping)
    {
        if (sf::Keyboard::isKeyPressed(pair.first))
        {
            return pair.second;
        }
    }

    return Action{ ActionType::Standing, Direction::Stay };
}

Player::~Player()
{
}