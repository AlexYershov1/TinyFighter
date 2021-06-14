#pragma once
#include "specialAttack/DynamicAttack.h"

DynamicAttack::DynamicAttack(const sf::Vector2f& location, AttackType attack, std::shared_ptr<Character> owner)
	: SpecialAttack(location, attack, owner),
	  m_dir(owner->getDirection())
{
	switch (attack)
	{
	case AttackType::Fire:
		m_speed = 10.f;
		break;
	case AttackType::Ice:
		m_speed = 5.f;
		break;
	default:
		throw std::runtime_error("received a non-dynamic attack");
		break;
	}
}

void DynamicAttack::update(const sf::Time& deltaTime)
{
	m_picture.move(convert(m_dir) * SPEED * deltaTime.asSeconds());

	if (outOfBounds(this->m_picture.getPosition()))
		DynamicAttack::~DynamicAttack();

	m_animation.update(deltaTime, m_dir);
}

DynamicAttack::~DynamicAttack()
{
}
