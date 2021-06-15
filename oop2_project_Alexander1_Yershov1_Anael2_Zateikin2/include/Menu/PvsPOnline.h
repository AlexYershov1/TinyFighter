#pragma once
#include "Menu/Command.h"


class PvsPOnline : public Command
{
public:
	PvsPOnline();
	~PvsPOnline();
	virtual void execute(sf::RenderWindow&, Arena&);

private:
	//ChooseCharacterMenu

};
