#pragma once
#include "GenericMenu.h"
#include "ChooseDifficulty.h"

class EnemyChoice : public GenericMenu
{
public:
	EnemyChoice();
	~EnemyChoice();
	void activateEnemyChoice(sf::RenderWindow&, Arena&);
	virtual void draw(sf::RenderWindow&) const;

private:
	//void setLocations();
	virtual bool handleClick(const sf::Vector2f&, sf::RenderWindow&, Arena&);
	virtual void handleMove(const sf::Vector2f&);

	void mark(sf::Text& text);

	void unmark(sf::Text& text);

	std::vector<std::pair<sf::Text, void(*)(sf::RenderWindow&, Arena&)>> m_choices;
	//ChooseDifficulty m_chooseDifficulty;
};
void noEnemies(sf::RenderWindow&, Arena&);
void withEnemies(sf::RenderWindow&, Arena&);
