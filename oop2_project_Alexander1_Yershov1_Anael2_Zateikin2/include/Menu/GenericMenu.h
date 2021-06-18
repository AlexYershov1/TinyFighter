#pragma once
#include <SFML/Graphics.hpp>
#include "macros.h"
#include "ResourcesManager.h"

class Arena;

class GenericMenu
{
public:
	GenericMenu();
	virtual ~GenericMenu();
	
	virtual void draw(sf::RenderWindow&) const = 0;
	
protected:
	void activateWindow(sf::RenderWindow& window, Arena&);
	void setBackground(sf::Texture*);
	virtual bool handleClick(const sf::Vector2f&, sf::RenderWindow&, Arena&) = 0;
	virtual void handleMove(const sf::Vector2f&) = 0;

	sf::Text m_header;
	sf::RectangleShape m_background;
};
