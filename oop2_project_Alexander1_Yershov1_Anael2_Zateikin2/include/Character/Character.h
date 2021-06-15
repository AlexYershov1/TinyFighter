#pragma once
#include "GameObject.h"
#include <cmath>

class Character : public GameObject
{
public:
	Character(const sf::Vector2f&, CharacterType);
	virtual void move(const sf::Time&);
	void update(const sf::Time&);
	ActionType getActionType() const;
	void setAction(Action);
	void setActionType(ActionType);
	bool facing(const sf::Vector2f*) const;
	bool facing(const Character&) const;
	Direction getDirection() const;
	~Character();
protected:
	Animation m_animation;
	std::pair<AttackType, AttackType> m_specialAttacks;
	int m_health, m_mana;

	float operator-(const sf::Vector2f*) const;
	float x() const;
	float y() const;
	bool enoughMana(ActionType) const;
private:

};
