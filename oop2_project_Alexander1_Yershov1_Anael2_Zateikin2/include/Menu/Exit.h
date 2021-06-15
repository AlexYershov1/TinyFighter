#pragma once
#include "Command.h"

class Exit: public Command
{
public:
	Exit();
	~Exit();
	virtual void execute(sf::RenderWindow&, Arena&);

private:

};
