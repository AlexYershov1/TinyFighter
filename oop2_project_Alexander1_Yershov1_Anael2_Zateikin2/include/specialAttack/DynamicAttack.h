#pragma once
#include "SpecialAttack.h"

class DynamicAttack : public SpecialAttack
{
public:
	DynamicAttack(const sf::Vector2f&, AttackType, Character*);
	virtual void update(const sf::Time&);
	virtual void move(const sf::Time&, Arena&);
	virtual ~DynamicAttack();

private:
	float m_speed;
};
