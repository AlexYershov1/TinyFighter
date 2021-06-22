#pragma once
#include <vector>
#include <memory>
//#include <SFML/Graphics.hpp>
#include "macros.h"
#include "Collision.h"
#include "specialAttack/DynamicAttack.h"
#include "specialAttack/StaticAttack.h"
#include "specialAttack/SpecialAttack.h"
#include "Menu/ConclusionWindow.h"
#include "Network.h"



class Arena
{
public:
	Arena();

	/*
	* add enums for arenas, add game info to know how many objects and which
	* objects (characters) to build.
	*/

	void clear();
	void createPlayer(CharacterType);
	void createEnemy( CharacterType);	//inside get the players locations
	void createSpecialAttack(ActionType, AttackType, Character*);
	void setMode(Mode);
	Mode getMode() const;
	void setArenaBackground(ArenaType);

	void draw(sf::RenderWindow&);
	void move(const sf::Time&);
	void update(const sf::Time&);
	void collision(sf::RenderWindow&);
	sf::Vector2f getFirstPlayerPos() const;

	// online
	void createSocket();
	~Arena();

private:
	sf::RectangleShape m_background;
	sf::RectangleShape m_ground;
	Mode m_mode;
	
	std::vector <std::unique_ptr<GameObject>> m_gameObjects;
	std::vector<std::unique_ptr<GameObject>> m_tempHolder;
	std::vector<const sf::Vector2f*> m_playerLocations;

	void* m_socket;

	void activateConclusionWindow(bool, sf::RenderWindow&);
	bool isWon() const;
};
