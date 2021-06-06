#pragma once
#include "MovingObject/MovingObject.h"


MovingObject::MovingObject(const sf::Vector2f& location)
	: GameObject(location)
{
}

MovingObject::~MovingObject()
{
}