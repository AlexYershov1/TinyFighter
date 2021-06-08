#pragma once
#include "MovingObject/MovingObject.h"

class Character : public MovingObject
{
public:
	Character(const sf::Vector2f&, CharacterType);
	~Character();

protected:
	Action m_action;
	Animation m_animation;
private:

};
