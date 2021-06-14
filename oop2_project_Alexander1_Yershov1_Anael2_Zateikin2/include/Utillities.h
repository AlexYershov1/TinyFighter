#pragma once
#include "macros.h"

bool outOfBounds(const sf::Vector2f&);

//A struct that holds the info of a new stage.
struct StageInfo
{
	CharacterType m_playerType;
	ArenaType m_arenaType;
	Difficulty m_diffuculy;
};