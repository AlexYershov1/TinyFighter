#pragma once
#include "ChooseCharacter.h"
#include "ChooseArena.h"
#include "EnemyChoice.h"
//#include "ChooseDifficulty.h"


class PvsP : public Command
{
public:
	PvsP();
	~PvsP();

	virtual void execute(sf::RenderWindow&, Arena&);
private:
	ChooseCharacter m_chooseCharMenu;
	ChooseArena m_chooseArena;
	//EnemyChoice m_enemyChoice;
	//ChooseDifficulty m_chooseDifficulty;
};