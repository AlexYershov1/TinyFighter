#pragma once
#include "SpecialAttack.h"

class DynamicAttack : public SpecialAttack
{
public:
	DynamicAttack(const sf::Vector2f&, AttackType, std::shared_ptr<Character>);
	virtual void update(const sf::Time&);
	virtual ~DynamicAttack();

private:
	Direction m_dir;
	float m_speed;
};
