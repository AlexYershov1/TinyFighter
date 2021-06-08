#pragma once
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "macros.h"

struct AnimeMap
{
	using ListType = std::vector<sf::IntRect>;
	using DataType = std::unordered_map<ActionType, ListType>;
	DataType m_data;

};