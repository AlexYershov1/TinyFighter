#include "Menu/PvsC.h"


PvsC::PvsC()
{
}

PvsC::~PvsC()
{
}

const StageInfo PvsC::execute(sf::RenderWindow& window)
{
	StageInfo info;
	//activate character selection + add player's name to vector
	//auto charName = m_chooseCharMenu.activateChooseCharacter(window);
	//player 1
	info.characterNames.push_back(m_chooseCharMenu.activateChooseCharacter(window));

	//choose arena and difficulty


	//activate arena selection and difficulty +create Enemies
	return info;
}
