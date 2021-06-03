#pragma once
#include "MovingObject/MovingObject.h"

class Character : public MovingObject
{
public:
	Character();
	~Character();

protected:
	Action m_action;
private:

};
