#pragma once
#include "../Character/Character.h"

class Player : public Character
{
public:
	Player(const sf::Vector2f&, CharacterType);
	void update(sf::Time&);
	~Player();

private:
	Animation m_animation;
};
