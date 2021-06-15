#pragma once
#include "specialAttack/DynamicAttack.h"

DynamicAttack::DynamicAttack(const sf::Vector2f& location, AttackType attack, std::shared_ptr<Character> owner)
	: SpecialAttack(location, attack, owner)
{
	m_action = Action(ActionType::Standing, owner->getDirection());

	switch (attack)
	{
	case AttackType::FireDynamic:
		m_speed = 10.f;
		break;
	case AttackType::IceDynamic:
		m_speed = 5.f;
		break;
	default:
		throw std::runtime_error("received a non-dynamic attack");
		break;
	}
}

void DynamicAttack::update(const sf::Time& deltaTime)
{
	m_picture.move(convert(m_action.second) * SPEED * deltaTime.asSeconds());

	if (m_animation.update(deltaTime, m_action) || outOfBounds(this->m_picture.getPosition()))
		DynamicAttack::~DynamicAttack();
}

DynamicAttack::~DynamicAttack()
{
}
