#pragma once
#include "Character/Character.h"


class Player : public Character
{
public:
	Player(const sf::Vector2f&, CharacterType, bool);
	void move(const sf::Time&, Arena&);
	const sf::Vector2f* getLocation() const;
	int getPlayerNum() const;
	
	Action getActionFromKey(Arena&);
	
	virtual void draw(sf::RenderWindow&) const;
	virtual ~Player();

	void resetCount();
	static int getCount();
	
private:
	int m_playerNum;
	static int m_count;			//counter for players created
	bool m_puppet;				//if this player is a puppet, for online mode
};
