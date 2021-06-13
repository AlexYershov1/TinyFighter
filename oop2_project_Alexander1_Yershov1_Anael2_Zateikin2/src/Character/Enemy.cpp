#pragma warning ( disable : 6011)
#include "Character/Enemy.h"


Enemy::Enemy(std::vector<const sf::Vector2f*>& ply, const sf::Vector2f& location, CharacterType character)
	: Character(location, character),
	  m_players(ply)
{
	m_difficulty = rand() % 3;
}

void Enemy::move(const sf::Time& deltaTime)
{
	engageClosestPlayer();

	// makes enemy wait based on difficulity
	if (m_restTime.getElapsedTime().asSeconds() > m_difficulty)
	{
		if (m_restTime.getElapsedTime().asSeconds() > m_difficulty + WaitTime)
			m_restTime.restart();
		m_action = Action(ActionType::Standing, Direction::Stay);
	}

	Character::move(deltaTime);
}

void Enemy::engageClosestPlayer()
{
	const sf::Vector2f* res = nullptr;	// return value
	auto min = float(INT_MAX);
	float distance = 0.f;
	

	for (auto player : m_players)
	{
		distance = *this - player;
		if (distance < min)
		{
			min = distance;
			res = player;
		}
	}

	if (facing(res))
	{
		if (distance < collisionDistance)
			m_action = Action{ ActionType::Punching, Direction::Stay };
		//else if (abs(res->y - this->y()) < EPSILON)
			//attemptSpecialAbility(res);
		else
			m_action = Action{ ActionType::Walking, directionToPlayer(res) };
	}
	else
		m_action = Action{ ActionType::Walking, directionToPlayer(res) };
}

Direction Enemy::directionToPlayer(const sf::Vector2f* ply) const
{
	auto axis = rand() % 2;

	switch (axis)	// get closer to player based on different axis
	{
	case YAxis:
		if (ply->y > this->y() && abs(ply->y - this->y()) > EPSILON)	// if player is below
			return Direction::Down;
		if (ply->y < this->y() && abs(ply->y - this->y()) > EPSILON)	// if player is above
			return Direction::Up;
		break;
	case XAxis:
		if (ply->x > this->x() && abs(ply->x - this->x()) > EPSILON)	// if player is to the right of enemy 
			return Direction::Right;
		if (ply->x < this->x() && abs(ply->x - this->x()) > EPSILON)	// if player is to the left of enemy
			return Direction::Left;
		break;
	default:
		break;
	}
	return m_action.second;
}
/*
bool Enemy::facingPlayer(const sf::Vector2f* player) const
{
	if ((this->m_picture.getScale().x < 0 && player->x < this->x()) ||
		 (this->m_picture.getScale().x > 0 && player->x > this->x()))
		return true;
	return false;
}
*/
void Enemy::attemptSpecialAbility(const sf::Vector2f* player)
{
	// TO-DO: initiate special ability
	// m_action = Action{ ActionType::SpecialAbility, Direction::Stay };
}
