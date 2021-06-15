#pragma once
#include "Command.h"
#include "ChooseCharacter.h"

//Player vs Computer button
class PvsC : public Command
{
public:
	PvsC();
	~PvsC();

	virtual void execute(sf::RenderWindow&, Arena&);
private:
	ChooseCharacter m_chooseCharMenu;
};
