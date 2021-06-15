#include "SpecialAttack\specialAttack.h"
#pragma once

SpecialAttack::SpecialAttack(const sf::Vector2f& location, AttackType attack, Character* owner)
	: GameObject(location),
	  m_animation(ResourcesManager::instance().animationData(attack), m_picture),
	  m_owner(owner),
	  m_kind(attack)
{
	m_picture.setTexture(ResourcesManager::instance().texture(int(attack), 0));
}

SpecialAttack::~SpecialAttack()
{
}
