#pragma warning ( disable : 6011)
#include "MovingObject/Character/Enemy.h"


Enemy::Enemy(const std::vector<std::shared_ptr<sf::Vector2f>>& ply, const sf::Vector2f& location, CharacterType character)
	: Character(location, character),
	  m_players(ply)
{
}

void Enemy::update(const sf::Time& deltaTime)
{
	engageClosestPlayer();

	m_picture.move(convert(m_action.second) * SPEED * deltaTime.asSeconds());
	m_animation.update(deltaTime, m_action);
}

void Enemy::engageClosestPlayer()
{
	sf::Vector2f* res = nullptr;	// return value
	auto min = float(INT_MAX);
	float distance = 0.f;
	auto collision = 10.f;

	for (auto& player : m_players)
	{
		distance = *this - player;
		if (distance < min)
		{
			min = distance;
			res = player.get();
		}
	}

	if (facingPlayer(res))
	{
		if (distance < collision)
			m_action = Action{ ActionType::Punching, Direction::Stay };
		else if (abs(res->y - this->y()) < EPSILON)
			attemptSpecialAbility(res);
		else
			m_action = Action{ ActionType::Walking, directionToPlayer(res) };
	}
	else
		m_action = Action{ ActionType::Walking, directionToPlayer(res) };
}

Direction Enemy::directionToPlayer(sf::Vector2f* ply) const
{
	auto axis = rand() % 2;

	switch (axis)	// get closer to player based on different axis
	{
	case YAxis:
		if (ply->y > this->y() && abs(ply->y - this->y()) > EPSILON)
			return Direction::Up;
		if (ply->y < this->y() && abs(ply->y - this->y()) > EPSILON)
			return Direction::Down;
		break;
	case XAxis:
		if (ply->x > this->x() && ply->x - this->x() > EPSILON)
			return Direction::Left;
		if (ply->y > this->x() && ply->y - this->x() > EPSILON)
			return Direction::Right;
		break;
	default:
		break;
	}
	return Direction::Stay;
}

bool Enemy::facingPlayer(sf::Vector2f* player) const
{
	if ((this->m_action.second == Direction::Left && player->x < this->x()) ||
		(this->m_action.second == Direction::Right && player->x > this->x()))
		return true;
	return false;
}

void Enemy::attemptSpecialAbility(sf::Vector2f* player)
{
	// TO-DO: initiate special ability
	// m_action = Action{ ActionType::SpecialAbility, Direction::Stay };
}
