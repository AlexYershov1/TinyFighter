#pragma once
#include "Menu/Command.h"


class PvsPOnline : public Command
{
public:
	PvsPOnline();
	~PvsPOnline();
	virtual const StageInfo execute(sf::RenderWindow&);

private:
	//ChooseCharacterMenu

};
