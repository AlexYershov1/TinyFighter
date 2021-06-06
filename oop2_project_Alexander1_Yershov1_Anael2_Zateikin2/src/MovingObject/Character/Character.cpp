#pragma once
#include "MovingObject/Character/Character.h"

Character::Character(const sf::Vector2f& location)
	: MovingObject(location), m_action(Action::Standing)
{
}

Character::~Character()
{
}