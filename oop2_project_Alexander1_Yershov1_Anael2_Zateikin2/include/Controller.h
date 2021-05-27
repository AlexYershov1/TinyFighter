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
	sf::RenderWindow m_gameWindow;
};

Controller::Controller()
{
}

Controller::~Controller()
{
}