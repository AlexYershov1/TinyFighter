#pragma once
#include "specialAttack/StaticAttack.h"
#include "..\..\include\SpecialAttack\StaticAttack.h"

StaticAttack::StaticAttack(const sf::Vector2f& location, AttackType attack, std::shared_ptr<Character> owner)
	: SpecialAttack(location, attack, owner)
{
}

void StaticAttack::update(const sf::Time& deltaTime)
{
	m_animation.update(deltaTime, Direction::Stay);
}

StaticAttack::~StaticAttack()
{
}
