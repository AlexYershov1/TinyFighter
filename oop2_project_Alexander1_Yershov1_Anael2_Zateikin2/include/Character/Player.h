#pragma once
#include "Character/Character.h"


class Player : public Character
{
public:
	Player(const sf::Vector2f&, CharacterType);
	void move(const sf::Time&, Arena&);
	
	const sf::Vector2f* getLocation() const;

	Action getActionFromKey(Arena&);
	virtual ~Player();
	virtual void draw(sf::RenderWindow&) const;

	static int getCount();
	void resetCount();
private:
	int m_playerNum;
	static int m_count;
};
