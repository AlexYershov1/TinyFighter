#pragma once
#include "ResourcesManager.h"
#include "Utillities.h"
#include "macros.h"
#include "Character/ManaAndHealth.h"
#include <SFML/Graphics.hpp>

class StatesSection
{
public:
	StatesSection();
	~StatesSection();


private:
	sf::RectangleShape m_template;
};