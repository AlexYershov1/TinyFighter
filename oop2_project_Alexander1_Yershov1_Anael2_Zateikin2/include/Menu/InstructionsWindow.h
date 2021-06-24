#pragma once
#include "GenericMenu.h"

class InstructionsWindow : GenericMenu
{
public:
	InstructionsWindow();
	~InstructionsWindow();

	void activateInstructionsWindow(sf::RenderWindow&, Arena&);
	void addText(const std::string&, sf::Vector2f);

	virtual void draw(sf::RenderWindow&) const;
private:
	void modifyButtons(float, int);
	virtual bool handleClick(const sf::Vector2f&, sf::RenderWindow&, Arena&);
	virtual void handleMove(const sf::Vector2f&) {}

	std::vector<sf::Text> m_texts;
	std::vector<sf::Sprite> m_buttons;
};