#pragma once
#include <vector>
#include <memory>
//#include <SFML/Graphics.hpp>
#include "macros.h"
#include "Collision.h"
#include "specialAttack/DynamicAttack.h"
#include "specialAttack/StaticAttack.h"
#include "specialAttack/SpecialAttack.h"



class Arena
{
public:
	Arena();

	/*
	* add enums for arenas, add game info to know how many objects and which
	* objects (characters) to build.
	*/

	void createArena();
	void createPlayer(CharacterType);
	void createEnemy( CharacterType);	//inside get the players locations
	void createSpecialAttack(ActionType, AttackType, Character*);

	void setArenaBackground(ArenaType);

	void draw(sf::RenderWindow&);
	void move(const sf::Time&);
	void update(const sf::Time&);
	void collision();
	sf::Vector2f getFirstPlayerPos() const;
	~Arena();

private:
	sf::RectangleShape m_background;
	sf::RectangleShape m_ground;
	
	std::vector <std::unique_ptr<GameObject>> m_gameObjects;
	std::vector<std::unique_ptr<GameObject>> m_tempHolder;
	std::vector<const sf::Vector2f*> m_playerLocations;
};
