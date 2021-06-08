#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	
	Enemy(/*vector of players' loctions*/const sf::Vector2f& , CharacterType );
	virtual ~Enemy() = default;

private:
};
