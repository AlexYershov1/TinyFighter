#include "Menu/PvsPOnline.h"

PvsPOnline::PvsPOnline()
{
}

PvsPOnline::~PvsPOnline()
{
}

void PvsPOnline::execute(sf::RenderWindow& window, Arena& arena)
{
	//open a socket

	m_chooseCharMenu.activateChooseCharacter(window, arena);
	
}
