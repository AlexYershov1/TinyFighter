#pragma once
#include "Character.h"

#include "Player.h"

class Enemy : public Character
{
public:
	Enemy(std::vector<const sf::Vector2f*>&, const sf::Vector2f&, CharacterType);
	void update(const sf::Time&);
	virtual ~Enemy() = default;

private:
	std::vector<const sf::Vector2f*> m_players;

	void engageClosestPlayer();
	Direction directionToPlayer(const sf::Vector2f*) const;
	bool facingPlayer(const sf::Vector2f*) const;
	void attemptSpecialAbility(const sf::Vector2f*);
};
