#pragma once
#include "Utillities.h"
#include "Character/Character.h"
#include <cmath>

bool outOfBounds(const sf::Vector2f& location)
{
	if (location.x < 0 || location.x > FULL_WINDOW_W ||
		location.y < WINDOW_HEIGHT - TERRAIN_HIGHT - 30 ||
		location.y > WINDOW_HEIGHT - 35)
		return true;
	return false;
}

//if received direction left and looking right or received direction right and looking left
void correctDir(sf::Sprite& pic, Direction dir)
{
	if ((dir == Direction::Left && pic.getScale().x > 0) ||
		(dir == Direction::Right && pic.getScale().x < 0))
		pic.scale(-1, 1);
}

void twoCharactersCollision(Character& first, Character& second)
{
	static Effect effect {(int)ActionType::Smacked};	// sound effect
	
	//if one of them is dead
	if ((!first.isAlive() && !first.isFaded()) || (!second.isAlive() && !second.isFaded()))
		return;

	//check if someone is punching
	if ((first.getActionType() == ActionType::Punching || first.punchDelayed()) && (first.facing(second)) )
	{
		if (effect.getStatus() != sf::Sound::Playing)
			effect.play();

		second.setActionType(ActionType::Smacked);

		if (!first.punchDelayed())
			second.decreaseHealth(PUNCH_DAMAGE);
	}
}