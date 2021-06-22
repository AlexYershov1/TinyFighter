#pragma once
#include "GenericMenu.h"

class ConclusionWindow : public GenericMenu
{
public:
	ConclusionWindow(bool);
	~ConclusionWindow();

	void activateConclusionWindow(sf::RenderWindow&, Arena&);
	void addText(const std::string&);
	virtual void draw(sf::RenderWindow&) const;
private:
	void setTextsLocations(); //places the text on window according to amount in vector
	virtual bool handleClick(const sf::Vector2f&, sf::RenderWindow&, Arena&);
	virtual void handleMove(const sf::Vector2f&) {}

	// change to pair
	std::vector<sf::Text> m_texts;
};