#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "ResourcesManager.h"
#include "Utillities.h"
#include "Arena.h"

class Command
{
public:
	Command();
	virtual ~Command() = default;
	virtual void execute(sf::RenderWindow&, Arena&) = 0;

private:
	
};
