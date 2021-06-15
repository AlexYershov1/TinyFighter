#pragma once
#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "Utillities.h"
#include "Arena.h"
#include "Command.h"
#include <string>
#include <memory>

class Menu
{
public:
	Menu();
	~Menu();

	StageInfo activateMenu(sf::RenderWindow&, Arena&) ; //const ?
	void draw(sf::RenderWindow&) const;
	void addCommand(const std::string&, std::unique_ptr<Command>);
private:
	typedef std::pair < sf::Text, std::unique_ptr<Command>> option;
	std::vector<option> m_options;
	sf::Text m_header;
	sf::RectangleShape m_background;

	
	StageInfo handleClick(const sf::Vector2f&, sf::RenderWindow&) const;
	void handleMove(const sf::Vector2f&);
	void setButton(sf::Text&,const std::string&, const sf::Vector2f&);
};
