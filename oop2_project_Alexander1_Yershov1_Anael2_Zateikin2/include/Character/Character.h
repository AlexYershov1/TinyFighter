#pragma once
#include "GameObject.h"
#include "ManaAndHealth.h"
#include <cmath>

class Character : public GameObject
{
public:
	Character(const sf::Vector2f&, CharacterType);
	virtual void move(const sf::Time&, Arena&);
	virtual void correctOwnersPtr() {}
	void update(const sf::Time&);
	ActionType getActionType() const;
	sf::Vector2f getLocation() const;
	void setAction(Action);
	void setActionType(ActionType);
	bool facing(const sf::Vector2f*) const;
	bool facing(const Character&) const;
	bool isMe(const Character* other) const { return &(*this) == &(*other); }
	Direction getDirection() const;
	Direction getFacingDirection() const;
	sf::Vector2f getOrigin();
	sf::FloatRect getBoundingRectangle() const;
	~Character();
protected:
	Animation m_animation;
	std::pair<AttackType, AttackType> m_specialAttacks;	// first is dynamic and second is static
	//int m_health, m_mana;
	sf::Clock m_specialAttackClock;
	sf::Clock m_disabled;
	ManaAndHealth m_manaAndHealth;

	float operator-(const sf::Vector2f*) const;
	float x() const;
	bool enoughMana(ActionType) const;
	bool inDisabledState(const sf::Time&);
private:

};
