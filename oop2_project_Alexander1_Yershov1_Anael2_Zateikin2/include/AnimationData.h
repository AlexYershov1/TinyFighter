#pragma once
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

struct AnimeMap
{
	using ListType = std::vector<sf::IntRect>;
	using DataType = std::unordered_map<Action, ListType>;
	DataType m_data;

};