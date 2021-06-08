#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "macros.h"
#include "ResourcesManager.h"



class Arena
{
public:
	Arena();

	/*
	* add enums for arenas, add game info to know how many objects and which
	* objects (characters) to build.
	*/

	void createArena(/*gameInfo*/);
	void draw(sf::RenderWindow&);
	bool outOfBounds(const sf::Vector2f&);
	~Arena();

private:
	sf::RectangleShape m_background;
	sf::RectangleShape m_ground;
	//sf::Sprite m_background;
	//sf::Sprite m_ground;
	//std::vector <unique_ptr GameObject> m_gameObjects;
};
