#pragma once
#include "MovingObject/Character/Character.h"

Character::Character(const sf::Vector2f& location, CharacterType character)
	: MovingObject(location), m_action(ActionType::Standing, Direction::Stay),
	  m_animation(ResourcesManager::instance().animationData(character), m_picture)
{
	m_picture.setTexture(ResourcesManager::instance().texture(character));
	m_picture.setOrigin(m_picture.getLocalBounds().height / 2, m_picture.getLocalBounds().width / 2);	// for correct rotation, setting origin at center
}

float Character::x() const
{
	return m_picture.getPosition().x;
}

float Character::y() const
{
	return m_picture.getPosition().y;
}

Character::~Character()
{
}

// find find the Euclidean distance between two characters
float Character::operator-(const std::unique_ptr<sf::Vector2f> &other) const
{
	return std::hypot(this->x() - other->x, this->y() - other->y);
}
