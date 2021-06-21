#include "Menu/PvsPOnline.h"

PvsPOnline::PvsPOnline()
{
}

PvsPOnline::~PvsPOnline()
{
}

void PvsPOnline::execute(sf::RenderWindow& window, Arena& arena)
{
	m_chooseModeMenu.activateChooseMode(window, arena);

	m_chooseCharMenu.activateChooseCharacter(window, arena);
	if (arena.getMode() == Mode::Server)
	{
		//open a socket TO_DO
		//choose arena 
		m_chooseArena.activateChooseArena(window, arena);

		//activate arena selection and difficulty +create Enemies
		m_chooseDifficulty.activateChooseDifficulty(window, arena);
	}
	
}
