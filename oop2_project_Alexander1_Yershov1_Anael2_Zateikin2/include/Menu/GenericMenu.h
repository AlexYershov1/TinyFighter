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
	
	virtual void draw(sf::RenderWindow&) const ;
	
protected:
	void activateWindow(sf::RenderWindow& window, Arena&);
	void setBackground(sf::Texture*);
	void setHeader(const std::string&, float); //set the string and character size
	virtual bool handleClick(const sf::Vector2f&, sf::RenderWindow&, Arena&) = 0;
	virtual void handleMove(const sf::Vector2f&) = 0;
	sf::Text createText(const std::string&) const ;
	//void addText(const std::string&, void* (*)(sf::RenderWindow& window, Arena&));

	template <typename Vect>
	void alignButtonsOnScreen(Vect&); //alignes locations on screen 

	sf::Text m_header;
	sf::RectangleShape m_background;
	std::vector<std::pair<sf::Text, void* (*)(sf::RenderWindow& window, Arena&)>> m_textButtons;
	std::vector<sf::Sprite> m_spriteButtons;
	std::vector<sf::RectangleShape> m_rectButtons;

};


//receives a template vector of pairs and sets location for first in the pair
template<class Vect>
inline void GenericMenu::alignButtonsOnScreen(Vect& vect) 
{
	auto xOffset = WINDOW_WIDTH / float(vect.size() + 1);
	auto offsetScale = 1.f;
	for (auto& item : vect)
	{
		item.first.setOrigin(item.first.getLocalBounds().height / 2,
			item.first.getLocalBounds().width / 2);
		item.first.setPosition({ xOffset * offsetScale, CENTER.y });
		offsetScale++;
	}
}
