#pragma once
#include "../Character/Character.h"

class Player : public Character
{
public:
	Player(const sf::Vector2f&, CharacterType);
	void update(const sf::Time&);
	void setAction(Action);
	Action getActionFromKey() const;
	virtual ~Player();

private:
};
