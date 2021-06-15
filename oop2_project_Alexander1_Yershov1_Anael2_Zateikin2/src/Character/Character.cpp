#pragma once
#include "Character/Character.h"

Character::Character(const sf::Vector2f& location, CharacterType character)
	: GameObject(location),
	  m_animation(ResourcesManager::instance().animationData(character), m_picture),
	  m_mana(0), m_health(0)
{
	m_picture.setTexture(ResourcesManager::instance().texture((int)character, 0));
	m_picture.setOrigin(m_picture.getLocalBounds().height / 2, m_picture.getLocalBounds().width / 2);	// for correct rotation, setting origin at center
	m_action = Action(ActionType::Standing, Direction::Stay);
}

void Character::move(const sf::Time& deltaTime)
{
	m_picture.move(convert(m_action.second) * SPEED * deltaTime.asSeconds());

	if (outOfBounds(this->m_picture.getPosition()))
		m_picture.move(convert(opposite(m_action.second)) * SPEED * deltaTime.asSeconds());
}

void Character::update(const sf::Time& deltaTime)
{
	// add switch case that defines correct sprite
	m_animation.update(deltaTime, m_action);
}

ActionType Character::getActionType() const
{
	return m_action.first;

}

void Character::setAction(Action action)
{
	m_action = action;
}

void Character::setActionType(ActionType actType)
{
	m_action.first = actType;
}

bool Character::facing(const sf::Vector2f* other) const
{
	if ((this->m_picture.getScale().x < 0 && other->x < this->x()) ||
		(this->m_picture.getScale().x > 0 && other->x > this->x()))
		return true;
	return false;
}

bool Character::facing(const Character& other) const
{
	return facing(&other.m_picture.getPosition());
}

Direction Character::getDirection() const
{
	return m_action.second;
}

float Character::x() const
{
	return m_picture.getPosition().x;
}

float Character::y() const
{
	return m_picture.getPosition().y;
}

bool Character::enoughMana(ActionType attack) const
{
	if (attack == ActionType::SpecialDynamic && m_mana < MAX_MANA / 2 ||
		attack == ActionType::SpecialStatic && m_mana < MAX_MANA / 4)
		return false;
	return true;
}

Character::~Character()
{
}

// find find the Euclidean distance between two characters
float Character::operator-(const sf::Vector2f* other) const
{
	return std::hypot(this->x() - other->x, this->y() - other->y);
}
