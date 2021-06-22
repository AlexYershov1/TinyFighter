#pragma once
#include "ChooseCharacter.h"
#include "ChooseArena.h"
#include "ChooseDifficulty.h"

class PvsP : public Command
{
public:
	PvsP();
	~PvsP();

	virtual void execute(sf::RenderWindow&, Arena&);
private:
	ChooseCharacter m_chooseCharMenu;
	ChooseArena m_chooseArena;
	ChooseDifficulty m_chooseDifficulty;
};