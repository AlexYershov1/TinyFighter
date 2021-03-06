#pragma once
#include <memory>
#include "Collision.h"
#include "macros.h"
#include "Arena.h"
#include "Menu/Menu.h"
#include "StatesSection.h"

class Controller
{
public:
	Controller();
	~Controller();
	void restart();
	void run();
private:
	void alignView();

	//void draw();
	Menu m_menu;
	sf::RenderWindow m_gameWindow;
	sf::Clock m_elapsed = {};
	Arena m_arena;
	StatesSection m_states;
	sf::View m_view;
};
