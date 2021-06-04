#pragma once
#include "MovingObject/Character/Player.h"

Player::Player(const sf::Vector2f& location , CharacterType character)
	: Character(location),
	  m_animation(ResourcesManager::instance().animationData(character), m_picture)
{
	m_picture.setTexture(ResourcesManager::instance().texture(character));
}

void Player::update(sf::Time& deltaTime)
{

}

Player::~Player()
{
}