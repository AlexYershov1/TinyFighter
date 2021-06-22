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
	void draw(sf::RenderWindow&) const;
	void move(); //stay on screen

	static void setRelativeStart(sf::Vector2f);
	static sf::Vector2f getRlativeStart();
private:
	sf::RectangleShape m_template;
	static sf::Vector2f m_relativeStarPos; //to keep the section on screen when view is changed
};
