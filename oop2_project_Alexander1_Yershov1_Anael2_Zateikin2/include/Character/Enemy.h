#pragma once
#include "Character.h"
//#include "Player.h"

class Enemy : public Character
{
public:
	Enemy(std::vector<const sf::Vector2f*>&, const sf::Vector2f&, CharacterType);
	void move(const sf::Time&, Arena&);
	virtual ~Enemy() = default;

private:
	std::vector<const sf::Vector2f*> m_players; //to chase players
	int m_difficulty;							//how often "rests"
	sf::Clock m_restTime = {};
	bool m_smart;	

	void engageClosestPlayer(Arena&);
	Direction directionToPlayer(const sf::Vector2f*) const;
	void attemptSpecialAbility(float, const sf::Vector2f*, Arena&);
};
