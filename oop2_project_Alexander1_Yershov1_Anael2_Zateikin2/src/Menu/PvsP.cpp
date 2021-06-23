#include "Menu/PvsP.h"

PvsP::PvsP()
{
}

PvsP::~PvsP()
{
}

void PvsP::execute(sf::RenderWindow& window, Arena& arena)
{
	//activate character selection + add player's name to vector
	m_chooseCharMenu.addSecondHeader("Player 1");
	m_chooseCharMenu.activateChooseCharacter(window, arena);		//player 1
	m_chooseCharMenu.setSecondHeader("Player 2");
	m_chooseCharMenu.activateChooseCharacter(window, arena);		//player 2
	
	//choose arena 
	m_chooseArena.activateChooseArena(window, arena);

	//with enemies / no enemies
	/*EnemyChoice enemyChoiceWindow;
	enemyChoiceWindow.activateEnemyChoice(window, arena);*/
	//m_chooseDifficulty.activateChooseDifficulty(window, arena);
}
