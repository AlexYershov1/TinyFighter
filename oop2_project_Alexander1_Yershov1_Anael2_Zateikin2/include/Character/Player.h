#pragma once
#include "Character/Character.h"


class Player : public Character
{
public:
	Player(const sf::Vector2f&, CharacterType, bool);
	void move(const sf::Time&, Arena&);
	const sf::Vector2f* getLocation() const;

	Action getActionFromKey(Arena&);
	virtual ~Player();
	virtual void draw(sf::RenderWindow&) const;

	static int getCount();
	int getPlayerNum() const;
	void resetCount();
private:
	int m_playerNum;
	static int m_count;
	bool m_puppet; // is this player a puppet, for online mode
};
