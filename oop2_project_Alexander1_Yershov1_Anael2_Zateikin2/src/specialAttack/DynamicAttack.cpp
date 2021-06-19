#pragma once
#include "specialAttack/DynamicAttack.h"

DynamicAttack::DynamicAttack(const sf::Vector2f& location, AttackType attack, Character* owner)
	: SpecialAttack(location, attack, owner)
{
	m_action = Action(ActionType::Standing, owner->getFacingDirection());
	m_picture.setPosition(location.x + OFFSET_SPECIAL_ATTACK_X * convert(owner->getFacingDirection()).x, location.y);
	correctDir(m_picture, owner->getFacingDirection());

	switch (attack)
	{
	case AttackType::FireDynamic:
		m_speed = RUN_SPEED;
		break;
	case AttackType::IceDynamic:
		m_speed = SPEED;
		break;
	default:
		throw std::runtime_error("received a non-dynamic attack");
		break;
	}
}

void DynamicAttack::update(const sf::Time& deltaTime)
{
	if (m_action.first == ActionType::hit)
	{
		m_animation.setAnimationTime(SlowAnimationTime);
		m_speed = 0;
	}
	
	if (m_animation.update(deltaTime, m_action) || outOfBounds(this->m_picture.getPosition()))
		m_alive = false;
}

void DynamicAttack::move(const sf::Time& deltaTime, Arena&)	//changed from SPEED to m_speed
{
	m_picture.move(convert(m_action.second) * m_speed * deltaTime.asSeconds());
}

DynamicAttack::~DynamicAttack()
{
}
