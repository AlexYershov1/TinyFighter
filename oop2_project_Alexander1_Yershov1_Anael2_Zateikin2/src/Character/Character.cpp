#pragma once
#include "Character/Character.h"

Character::Character(const sf::Vector2f& location, CharacterType character)
	: GameObject(location),
	  m_animation(ResourcesManager::instance().animationData(character), m_picture),
	  m_punchingDelayed(false)
{
	m_picture.setTexture(ResourcesManager::instance().texture((int)character, 0));
	m_picture.setOrigin(m_picture.getLocalBounds().height / 2, m_picture.getLocalBounds().width / 2);	// for correct rotation, setting origin at center
	m_action = Action(ActionType::Standing, Direction::Stay);
}

void Character::move(const sf::Time& deltaTime, Arena& arena)
{
	m_picture.move(convert(m_action.second) * m_speed * deltaTime.asSeconds());

	if (outOfBounds(this->m_picture.getPosition()))
		m_picture.move(convert(opposite(m_action.second)) * m_speed * deltaTime.asSeconds());
}

void Character::update(const sf::Time& deltaTime)
{
	if (m_action.first == ActionType::Standing && m_punchingClock.getElapsedTime().asSeconds() < PUNCHING_DELAY)
		m_animation.update(deltaTime, Action{ ActionType::Punching, m_action.second });
	else
	{
		m_animation.update(deltaTime, m_action);
		m_punchingDelayed = false;
	}
	m_manaAndHealth.increaseMana(deltaTime);
}

ActionType Character::getActionType() const
{
	return m_action.first;

}

sf::Vector2f Character::getLocation() const
{
	return m_picture.getPosition();
}

void Character::decreaseHealth(float value)
{
	m_manaAndHealth.decreaseHealth(value);
}

void Character::setAction(Action action)
{
	m_action = action;
}

void Character::setActionType(ActionType actType)
{
	if (actType == ActionType::Burning || actType == ActionType::Freezing)
		m_disabled.restart();	// make disabled
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

Direction Character::getFacingDirection() const
{
	return m_picture.getScale().x < 0 ? Direction::Left : Direction::Right;
}

sf::Vector2f Character::getOrigin()
{
	return m_picture.getOrigin();
}

sf::FloatRect Character::getBoundingRectangle() const
{
	return m_picture.getGlobalBounds();
}

bool Character::punchDelayed() const
{
	return m_punchingDelayed;
}

float Character::x() const
{
	return m_picture.getPosition().x;
}

bool Character::enoughMana(ActionType attack) const
{
	if (attack == ActionType::SpecialDynamic && m_manaAndHealth.getMana() >= 30 ||
		attack == ActionType::SpecialStatic && m_manaAndHealth.getMana() >= 20)
		return true;
	return false;
}

bool Character::inDisabledState(const sf::Time& deltaTime)
{
	static Effect burningEffect{ActionType::Burning}, freezingEffect{ActionType::Freezing};

	if (m_action.first == ActionType::Burning && m_disabled.getElapsedTime().asSeconds() < 0.5f)
	{
		if (burningEffect.getStatus() != sf::Sound::Playing)
			burningEffect.play();
		m_picture.move(convert(opposite(m_action.second)) * m_speed * deltaTime.asSeconds());
		m_manaAndHealth.decreaseHealth(deltaTime.asSeconds() * BURNING_DAMAGE);
		return true;
	}
	if (m_action.first == ActionType::Freezing && m_disabled.getElapsedTime().asSeconds() < 2.f)
	{
		if (freezingEffect.getStatus() != sf::Sound::Playing)
			freezingEffect.play();
		return true;
	}
	if ((m_action.first == ActionType::SpecialDynamic || m_action.first == ActionType::SpecialStatic) &&
		m_disabled.getElapsedTime().asSeconds() < 0.3)
		return true;

	if (m_action.first == ActionType::Punching && m_disabled.getElapsedTime().asSeconds() < PUNCHING_DELAY)
	{
		m_punchingDelayed = true;
  		m_action.first = ActionType::Standing;
		return true;
	}
	return false;
}

Character::~Character()
{
}

// finds the Euclidean distance between two characters
float Character::operator-(const sf::Vector2f* other) const
{
	return std::hypot(this->x() - other->x, this->y() - other->y);
}
