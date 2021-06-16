#include "specialAttack/StaticAttack.h"

StaticAttack::StaticAttack(const sf::Vector2f& location, AttackType attack, Character* owner)
	: SpecialAttack(location, attack, owner)
{
	m_action = Action(ActionType::hit, Direction::Stay);
}

void StaticAttack::update(const sf::Time& deltaTime)
{
	if (m_animation.update(deltaTime, m_action))
		//StaticAttack::
		return;
}

StaticAttack::~StaticAttack()
{
}

void StaticAttack::setLife()
{
	return;
}
