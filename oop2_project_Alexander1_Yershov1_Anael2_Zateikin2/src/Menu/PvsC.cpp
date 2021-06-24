#include "Menu/PvsC.h"


PvsC::PvsC()
{
}

PvsC::~PvsC()
{
}

void PvsC::execute(sf::RenderWindow& window, Arena& arena)
{
	
	//activate character selection + create player
	ChooseCharacter m;
	m.activateChooseCharacter(window, arena);	//player 1
	
	//choose arena 
	m_chooseArena.activateChooseArena(window, arena);

	//activate arena selection and difficulty +create Enemies
	m_chooseDifficulty.activateChooseDifficulty(window, arena);
}
