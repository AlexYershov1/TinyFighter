#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	
	Enemy(/*vector of players' loctions*/const sf::Vector2f& , CharacterType );
	~Enemy() = default;

private:
	Animation m_animation;
};
