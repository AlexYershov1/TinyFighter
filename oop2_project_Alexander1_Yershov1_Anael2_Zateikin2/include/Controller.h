#pragma once
#include <memory>
#include "macros.h"

class Controller
{
public:
	Controller();
	~Controller();
	void run();
private:
	//void draw();
	sf::RenderWindow m_gameWindow;
	sf::Time m_elapsed = {};
};
