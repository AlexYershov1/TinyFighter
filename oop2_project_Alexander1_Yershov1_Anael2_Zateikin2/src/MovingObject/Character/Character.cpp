#pragma once
#include "MovingObject/Character/Character.h"

Character::Character(const sf::Vector2f& location, CharacterType character)
	: MovingObject(location), m_action(ActionType::Standing, Direction::Stay),
	  m_animation(ResourcesManager::instance().animationData(character), m_picture)
{
	m_picture.setTexture(ResourcesManager::instance().texture(character));
	m_picture.setOrigin(m_picture.getLocalBounds().height / 2, m_picture.getLocalBounds().width / 2);	// for correct rotation, setting origin at center
}

Character::~Character()
{
}