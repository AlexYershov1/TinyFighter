#pragma once
#include "Menu/Command.h"
#include "ChooseCharacter.h"


class PvsPOnline : public Command
{
public:
	PvsPOnline();
	~PvsPOnline();
	virtual void execute(sf::RenderWindow&, Arena&);

private:
	ChooseCharacter m_chooseCharMenu;

};
