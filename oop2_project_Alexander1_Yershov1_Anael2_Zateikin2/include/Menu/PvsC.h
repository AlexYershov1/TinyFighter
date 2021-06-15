#pragma once
#include "Command.h"
#include "ChooseCharacter.h"

//Player vs Computer button
class PvsC : public Command
{
public:
	PvsC();
	~PvsC();

	virtual const StageInfo execute(sf::RenderWindow&);
private:
	ChooseCharacter m_chooseCharMenu;
};
