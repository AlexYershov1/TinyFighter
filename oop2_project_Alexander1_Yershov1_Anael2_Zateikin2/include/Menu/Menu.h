#pragma once
//#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "ResourcesManager.h"
#include "Utillities.h"
#include "Arena.h"
#include "Command.h"
#include "GenericMenu.h"


class Menu : public GenericMenu
{
public:
	Menu();
	~Menu();

	void activateMenu(sf::RenderWindow&, Arena&) ;
	virtual void draw(sf::RenderWindow&) const;
	void addCommand(const std::string&, std::unique_ptr<Command>);
private:
	typedef std::pair < sf::Text, std::unique_ptr<Command>> option;
	std::vector<option> m_options;

	
	virtual bool handleClick(const sf::Vector2f&, sf::RenderWindow&, Arena&) ;
	virtual void handleMove(const sf::Vector2f&);
	void setButton(sf::Text&,const std::string&, const sf::Vector2f&);
};
