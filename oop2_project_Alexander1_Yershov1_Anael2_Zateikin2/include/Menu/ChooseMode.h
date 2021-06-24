#pragma once
#include "GenericMenu.h"

class ChooseMode : public GenericMenu
{
public:
	ChooseMode();
	~ChooseMode();

	void activateChooseMode(sf::RenderWindow&, Arena&);
	void addText(const std::string&);
	virtual void draw(sf::RenderWindow&) const;
private:
	void setTextsLocations(); //places the text on window according to amount in vector
	virtual bool handleClick(const sf::Vector2f&, sf::RenderWindow&, Arena&);
	virtual void handleMove(const sf::Vector2f&);

	void mark(sf::Text&);
	void unmark(sf::Text&);

	std::vector<sf::Text> m_options;
};