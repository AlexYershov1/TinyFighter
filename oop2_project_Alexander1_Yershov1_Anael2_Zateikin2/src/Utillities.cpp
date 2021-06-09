#pragma once
#include "Utillities.h"

bool outOfBounds(const sf::Vector2f& location)
{
	if (location.x < 0 || location.x > WINDOW_WIDTH ||
		location.y < WINDOW_HEIGHT - TERRAIN_HIGHT - 30 ||
		location.y > WINDOW_HEIGHT - 35)
		return true;
	return false;
}