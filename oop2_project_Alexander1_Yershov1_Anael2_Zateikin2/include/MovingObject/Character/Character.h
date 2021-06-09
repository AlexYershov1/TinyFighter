#pragma once
#include "MovingObject/MovingObject.h"
#include <cmath>

class Character : public MovingObject
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

	~Character();
protected:
	Action m_action;
	Animation m_animation;

	float operator-(const sf::Vector2f*) const;
	float x() const;
	float y() const;
private:

};
