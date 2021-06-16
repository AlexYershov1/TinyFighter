#pragma once
#include "SpecialAttack.h"

class StaticAttack : public SpecialAttack
{
public:
	StaticAttack(const sf::Vector2f&, AttackType, Character*);
	virtual void update(const sf::Time&);
	virtual ~StaticAttack();
	void setLife();
private:
};