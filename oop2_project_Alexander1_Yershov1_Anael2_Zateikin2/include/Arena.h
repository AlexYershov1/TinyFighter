#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "macros.h"
#include "ResourcesManager.h"
#include "Utillities.h"
#include "GameObject.h"
#include "Collision.h"



class Arena
{
public:
	Arena();

	/*
	* add enums for arenas, add game info to know how many objects and which
	* objects (characters) to build.
	*/

	void createArena(const StageInfo&);
	void createPlayer(const sf::Vector2f&, CharacterType);
	void createEnemy(const sf::Vector2f&, CharacterType);	//inside get the players locations

	void draw(sf::RenderWindow&);
	void move(const sf::Time&);
	void update(const sf::Time&);
	void collision();
	~Arena();

private:
	sf::RectangleShape m_background;
	sf::RectangleShape m_ground;
	
	std::vector <std::shared_ptr<GameObject>> m_gameObjects;
	std::vector<const sf::Vector2f*> m_playerLocations;
};
