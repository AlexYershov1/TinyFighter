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

	void clear();						//clear all vectors and data
	void createPlayer(CharacterType, bool);	
	void createEnemy( CharacterType);
	void createSpecialAttack(ActionType, AttackType, Character*);
	void setMode(Mode);					//for online game
	Mode getMode() const;
	void setArenaBackground(ArenaType);

	void draw(sf::RenderWindow&);
	void move(const sf::Time&);
	void update(const sf::Time&);
	void collision(sf::RenderWindow&);
	sf::Vector2f getFirstPlayerPos() const;

	// online
	void createSocket();
	static void* m_socket;
	~Arena();

private:
	sf::RectangleShape m_background;
	sf::RectangleShape m_ground;
	Mode m_mode;
	
	std::vector <std::unique_ptr<GameObject>> m_gameObjects;
	std::vector<std::unique_ptr<GameObject>> m_tempHolder;	//for new objects to be inserted in vector
	std::vector<const sf::Vector2f*> m_playerLocations;		//for enemies

	void activateConclusionWindow(bool, sf::RenderWindow&);
	bool isWon() const;
};
