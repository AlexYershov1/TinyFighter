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
	//void addText(const std::string&, void*);
	//void add

	template <typename Vect>
	void alignButtonsOnScreen(Vect&, bool); //alignes locations on screen horisontal/vertical

	sf::Text m_header;
	sf::RectangleShape m_background;
	std::vector<sf::Text> m_textButtons;
	std::vector<sf::Sprite> m_spriteButtons;
	std::vector<sf::RectangleShape> m_rectButtons;

};

template<typename Vect>
inline void GenericMenu::alignButtonsOnScreen(Vect&, bool)
{
	auto xOffset = WINDOW_WIDTH / float(Vect.size() + 1);
	auto offsetScale = 1.f;
	for (auto& item : Vect)
	{
		item.first.setOrigin(item.first.getLocalBounds().height / 2,
			item.first.getLocalBounds().width / 2);
		item.first.setPosition({ xOffset * offsetScale, CENTER.y });
		offsetScale++;
	}
}
