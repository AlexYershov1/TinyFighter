#pragma once
#include "Character.h"

#include "Player.h"

class Enemy : public Character
{
public:
	Enemy(const std::vector<std::unique_ptr<sf::Vector2f>>&, const sf::Vector2f&, CharacterType);
	void update(const sf::Time&);
	virtual ~Enemy() = default;

private:
	const std::vector<std::unique_ptr<sf::Vector2f>> m_players;

	void engageClosestPlayer();
	Direction directionToPlayer(sf::Vector2f*) const;
	bool facingPlayer(sf::Vector2f*) const;
	void attemptSpecialAbility(sf::Vector2f*);
};
