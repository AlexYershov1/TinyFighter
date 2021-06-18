#include "Menu/PvsC.h"


PvsC::PvsC()
{
}

PvsC::~PvsC()
{
}

void PvsC::execute(sf::RenderWindow& window, Arena& arena)
{
	
	//activate character selection + add player's name to vector
	m_chooseCharMenu.activateChooseCharacter(window, arena);		//player 1
	
	//choose arena 
	m_chooseArena.activateChooseArena(window, arena);

	//activate arena selection and difficulty +create Enemies
	m_chooseDifficulty.activateChooseDifficulty(window, arena);
}
