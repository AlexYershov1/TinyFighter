#pragma once
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "macros.h"

struct AnimeMap
{
	//a map with keys = ActionType , and value = vector of IntRect
	//holds a vector of a cut sprite sheet
	using ListType = std::vector<sf::IntRect>;
	using DataType = std::unordered_map<ActionType, ListType>;
	DataType m_data;

};