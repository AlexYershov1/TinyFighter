#pragma once
#include "MovingObject/Character/Character.h"

Character::Character(const sf::Vector2f& location, CharacterType character)
	: MovingObject(location), m_action(ActionType::Standing, Direction::Stay),
	  m_animation(ResourcesManager::instance().animationData(character), m_picture)
{
	m_picture.setTexture(ResourcesManager::instance().texture(character));
	m_picture.setOrigin(m_picture.getLocalBounds().height / 2, m_picture.getLocalBounds().width / 2);	// for correct rotation, setting origin at center
}

void Character::update(const sf::Time& deltaTime)
{
	m_picture.move(convert(m_action.second) * SPEED * deltaTime.asSeconds());
	if (outOfBounds(this->m_picture.getPosition()))
		m_picture.move(convert(opposite(m_action.second)) * SPEED * deltaTime.asSeconds());
	m_animation.update(deltaTime, m_action);
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
float Character::operator-(const sf::Vector2f* other) const
{
	return std::hypot(this->x() - other->x, this->y() - other->y);
}
