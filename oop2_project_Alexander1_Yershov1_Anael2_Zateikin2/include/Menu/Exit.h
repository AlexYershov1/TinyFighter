#pragma once
#include "Command.h"

class Exit: public Command
{
public:
	Exit();
	~Exit();
	virtual const StageInfo execute(sf::RenderWindow&);

private:

};
