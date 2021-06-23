#pragma warning ( disable : 6011)
#include "Character/Enemy.h"
#include "Arena.h"


Enemy::Enemy(std::vector<const sf::Vector2f*>& ply, const sf::Vector2f& location, CharacterType character)
	: Character(location, character),
	  m_players(ply)
{
	m_difficulty = rand() % 3;
	m_smart = character == CharacterType::Bandit ? false : true;
	m_specialAttacks = character == CharacterType::Bandit ? 
		std::make_pair(AttackType::None, AttackType::None) : std::make_pair(AttackType::None, AttackType::None);
	m_puppet = false;
}

void Enemy::move(const sf::Time& deltaTime, Arena& arena)
{
	if (inDisabledState(deltaTime))
	{
		//Action(ActionType::Standing, Direction::Stay);
		return;
	}
	engageClosestPlayer(arena);

	// makes enemy wait based on difficulity
	if (m_restTime.getElapsedTime().asSeconds() > m_difficulty)
	{
		if (m_restTime.getElapsedTime().asSeconds() > m_difficulty + WaitTime)
			m_restTime.restart();
		m_action = Action(ActionType::Standing, Direction::Stay);
	}

	Character::move(deltaTime, arena);
}

void Enemy::engageClosestPlayer(Arena& arena)
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
		{
			if (m_disabled.getElapsedTime().asSeconds() > PUNCHING_DELAY + 1.5f)
			{
				m_action = Action{ ActionType::Punching, Direction::Stay };
				m_disabled.restart();
				m_punchingClock.restart();
			}
		}
		else if (abs(res->y - this->y()) < EPSILON && m_smart)
			attemptSpecialAbility(distance, res, arena);
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

void Enemy::attemptSpecialAbility(float distance, const sf::Vector2f* ply, Arena& arena)
{
	if (distance < collisionDistance + 30 && enoughMana(ActionType::SpecialStatic))
	{
		arena.createSpecialAttack(ActionType::SpecialStatic, m_specialAttacks.second, this);
		//m_disabled.restart();
		m_action.first = ActionType::SpecialStatic;
	}
	else if (enoughMana(ActionType::SpecialDynamic))
	{
		arena.createSpecialAttack(ActionType::SpecialDynamic, m_specialAttacks.first, this);
		//m_disabled.restart();
		m_action.first = ActionType::SpecialDynamic;
	}
	else
		m_action = Action{ ActionType::Walking, directionToPlayer(ply) };
}
