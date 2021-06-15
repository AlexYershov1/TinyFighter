#pragma once
#include "SpecialAttack.h"

class DynamicAttack : public SpecialAttack
{
public:
	DynamicAttack(const sf::Vector2f&, AttackType, Character*);
	virtual void update(const sf::Time&);
	virtual ~DynamicAttack();

private:
	float m_speed;
};
