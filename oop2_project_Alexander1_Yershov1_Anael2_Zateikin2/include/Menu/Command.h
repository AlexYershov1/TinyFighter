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
	virtual const StageInfo execute(sf::RenderWindow&) = 0;

private:
	
};
