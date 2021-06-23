#pragma once
#include "GenericMenu.h"

class ChooseArena : public GenericMenu
{
public:
	ChooseArena();
	~ChooseArena();
	ArenaType getChoice() const;
	void activateChooseArena(sf::RenderWindow&, Arena&);
	virtual void draw(sf::RenderWindow&) const;
private:
	virtual bool handleClick(const sf::Vector2f&, sf::RenderWindow&, Arena&) ;
	virtual void handleMove(const sf::Vector2f&) ;

	void modifyThumbnails();
	void mark(sf::RectangleShape&);
	void unmark(sf::RectangleShape&);
	std::vector<std::pair<sf::RectangleShape, ArenaType>> m_arenasThumbnails;
	std::pair<sf::RectangleShape, sf::RectangleShape> m_arrows;
	ArenaType m_choice;
};
