#pragma once
#include "specialAttack/DynamicAttack.h"

DynamicAttack::DynamicAttack(const sf::Vector2f& location, AttackType attack, Character* owner)
	: SpecialAttack(location, attack, owner)
{
	m_action = Action(ActionType::Standing, owner->getFacingDirection());
	m_picture.setPosition(location.x + OFFSET_SPECIAL_ATTACK_X * convert(owner->getFacingDirection()).x, location.y - OFFSET_SPECIAL_ATTACK_Y);
	correctDir(m_picture, owner->getFacingDirection());

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
	if (m_animation.update(deltaTime, m_action) || outOfBounds(this->m_picture.getPosition()))
		m_alive = false;
}

void DynamicAttack::move(const sf::Time& deltaTime, Arena&)
{
	m_picture.move(convert(m_action.second) * SPEED * deltaTime.asSeconds());
}

DynamicAttack::~DynamicAttack()
{
}
