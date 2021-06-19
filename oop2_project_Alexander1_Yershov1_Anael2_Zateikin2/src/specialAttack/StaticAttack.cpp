#include "specialAttack/StaticAttack.h"

StaticAttack::StaticAttack(const sf::Vector2f& location, AttackType attack, Character* owner)
	: SpecialAttack(location, attack, owner)
{
	m_action = Action(ActionType::hit, Direction::Stay);
	m_picture.setPosition(location.x - 35, location.y - 70);
}

void StaticAttack::update(const sf::Time& deltaTime)
{
	if (m_animation.update(deltaTime, m_action))
		m_alive = false;
}

StaticAttack::~StaticAttack()
{
}

void StaticAttack::setLife()
{
	return;
}
