#pragma once
#include <memory>
#include "macros.h"
#include "Arena.h"

class Controller
{
public:
	Controller();
	~Controller();
	void run();
private:
	//void draw();
	sf::RenderWindow m_gameWindow;
	sf::Clock m_elapsed = {};
	Arena m_arena;
};
