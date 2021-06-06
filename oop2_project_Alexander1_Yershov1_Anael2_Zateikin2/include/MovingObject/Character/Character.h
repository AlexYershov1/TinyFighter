#pragma once
#include "MovingObject/MovingObject.h"

class Character : public MovingObject
{
public:
	Character(const sf::Vector2f& location);
	~Character();

protected:
	Action m_action;
private:

};
