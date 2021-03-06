#pragma once
#include "SpecialAttack\specialAttack.h"
#include "Arena.h"

SpecialAttack::SpecialAttack(const sf::Vector2f& location, AttackType attack, Character* owner)
	: GameObject(location),
	  m_animation(ResourcesManager::instance().animationData(attack), m_picture),
	  m_owner(owner),
	  m_kind(attack)
{
	m_picture.setOrigin(owner->getOrigin());
	m_picture.setTexture(ResourcesManager::instance().texture(int(attack), 0));
}

void SpecialAttack::correctOwnersPtr()
{ 
	if (!ownerIsAlive())
		m_owner = nullptr;
}

void SpecialAttack::setHit()
{
	m_action.first = ActionType::hit;
	//m_alive = false;
}

bool SpecialAttack::ownerIsAlive() const
{
	return m_owner; //return false if nullptr
}

SpecialAttack::~SpecialAttack()
{
}
