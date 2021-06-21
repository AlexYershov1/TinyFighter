#pragma once
#include "Utillities.h"
#include "Character/Character.h"

bool outOfBounds(const sf::Vector2f& location)
{
	if (location.x < 0 || location.x > WINDOW_WIDTH ||
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
	static Effect effect {ActionType::Smacked};	// sound effect

	//check if someone is punching
	if ((first.getActionType() == ActionType::Punching || first.punchDelayed()) && (first.facing(second)))
	{
		if (effect.getStatus() != sf::Sound::Playing)
			effect.play();

		second.setActionType(ActionType::Smacked);

		if (!first.punchDelayed())
			second.decreaseHealth(PUNCH_DAMAGE);
	}
}