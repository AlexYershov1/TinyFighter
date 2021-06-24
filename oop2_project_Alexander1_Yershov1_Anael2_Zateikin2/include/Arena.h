#pragma once
#include <vector>
#include <memory>
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
	~Arena();

	void clear();						//clear all vectors and data
	void createPlayer(CharacterType, bool);	
	void createEnemy( CharacterType);
	void createSpecialAttack(ActionType, AttackType, Character*);
	void setArenaBackground(ArenaType);
	static void setMode(Mode);					//for online game
	static Mode getMode();
	
	void draw(sf::RenderWindow&);
	void move(const sf::Time&);
	void update(const sf::Time&);
	void collision(sf::RenderWindow&);
	sf::Vector2f getFirstPlayerPos() const; //get the location on first player

	// online
	void createSocket();
	static void* m_socket;
	
private:
	sf::RectangleShape m_background;
	sf::RectangleShape m_ground;
	static Mode m_mode;				//for online
	
	std::vector <std::unique_ptr<GameObject>> m_gameObjects;
	std::vector<std::unique_ptr<GameObject>> m_tempHolder;	//for new objects to be inserted in vector
	std::vector<const sf::Vector2f*> m_playerLocations;		//for enemies

	void activateConclusionWindow(bool, sf::RenderWindow&, int = OFFLINE);
	bool isWon() const;
};
