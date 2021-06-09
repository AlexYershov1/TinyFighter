#pragma once
#include "MovingObject/MovingObject.h"
#include <cmath>

class Character : public MovingObject
{
public:
	Character(const sf::Vector2f&, CharacterType);
	void update(const sf::Time&);
	~Character();
protected:
	Action m_action;
	Animation m_animation;

	float operator-(const sf::Vector2f*) const;
	float x() const;
	float y() const;
private:

};
