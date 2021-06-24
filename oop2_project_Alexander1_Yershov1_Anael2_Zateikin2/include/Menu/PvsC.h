#pragma once
#include "ChooseCharacter.h"
#include "ChooseArena.h"
#include "ChooseDifficulty.h"

//Player vs Computer button
class PvsC : public Command
{
public:
	PvsC();
	~PvsC();

	virtual void execute(sf::RenderWindow&, Arena&);
private:
	ChooseCharacter m_chooseCharMenu;
	ChooseArena m_chooseArena;
	ChooseDifficulty m_chooseDifficulty;
};
