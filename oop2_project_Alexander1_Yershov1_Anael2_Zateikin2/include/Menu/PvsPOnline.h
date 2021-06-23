#pragma once
#include "ChooseCharacter.h"
#include "ChooseMode.h"
#include "ChooseArena.h"
#include "ChooseDifficulty.h"


class PvsPOnline : public Command
{
public:
	PvsPOnline();
	~PvsPOnline();
	virtual void execute(sf::RenderWindow&, Arena&);

private:
	ChooseMode m_chooseModeMenu;
	ChooseCharacter m_chooseCharMenu;
	ChooseArena m_chooseArena;
	//ChooseDifficulty m_chooseDifficulty;

	void waitForOtherPlayer(sf::RenderWindow&);
};
