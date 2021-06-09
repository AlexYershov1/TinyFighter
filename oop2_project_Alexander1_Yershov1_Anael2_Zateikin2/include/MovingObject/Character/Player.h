#pragma once
#include "../Character/Character.h"

class Player : public Character
{
public:
	Player(const sf::Vector2f&, CharacterType);
	void update(const sf::Time&);
	void setAction(Action);
	const sf::Vector2f* getLocation() const;

	Action getActionFromKey() const;
	virtual ~Player();

private:
};
