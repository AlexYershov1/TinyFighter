#pragma once
#include "macros.h"
#include <vector>
#include <string>

bool outOfBounds(const sf::Vector2f&);

//A struct that holds the info of a new stage.
struct StageInfo
{
	StageInfo() {}
	StageInfo(const StageInfo& other) : characterNames(other.characterNames), arenaType(other.arenaType) {}
	StageInfo( std::vector<int> names, ArenaType type) : characterNames(names), arenaType(type) {}

	std::vector<int> characterNames;
	ArenaType arenaType;
};