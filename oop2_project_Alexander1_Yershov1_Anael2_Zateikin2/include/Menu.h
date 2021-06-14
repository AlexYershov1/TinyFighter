#pragma once
#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "Utillities.h"
#include "Arena.h"
#include <string>

class Menu
{
public:
	Menu();
	~Menu();

	void activateMenu(sf::RenderWindow&, Arena&) ; //const ?
	void draw(sf::RenderWindow&) const;

private:

	sf::Text m_header;
	sf::Text m_pVSpOnline;		//player vs player online
	sf::Text m_pVSp1Keyboard;	//two players on same keyboard
	sf::Text m_pVSc;			//player verses computer
	sf::Text m_exit;
	sf::RectangleShape m_background;

	bool handleClick(const sf::Vector2f&, sf::RenderWindow&) const;
	void handleMove(const sf::Vector2f&);
	void setButton(sf::Text&,const std::string&, const sf::Vector2f&);
};
