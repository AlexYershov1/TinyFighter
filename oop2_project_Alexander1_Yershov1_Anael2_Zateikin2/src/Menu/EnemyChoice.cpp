#include "Menu/EnemyChoice.h"


EnemyChoice::EnemyChoice()
{
	//header
	setHeader("Game mode", HEADER_SIZE);

	m_choices.push_back({ createText("no enemies"), noEnemies });
	m_choices.push_back({ createText("with enemies"), withEnemies });
	
	alignButtonsOnScreen(m_choices);
}

EnemyChoice::~EnemyChoice()
{
}

void EnemyChoice::activateEnemyChoice(sf::RenderWindow& window, Arena& arena)
{
	GenericMenu::activateWindow(window, arena);
}
void EnemyChoice::draw(sf::RenderWindow& window) const
{
	GenericMenu::draw(window);
	for (const auto& item : m_choices)
		window.draw(item.first);
}
bool EnemyChoice::handleClick(const sf::Vector2f& location, sf::RenderWindow& window, Arena& arena)
{
	for (const auto& choice : m_choices)
	{
		if (choice.first.getGlobalBounds().contains(location))
		{
			choice.second(window, arena);
			return true;
		}
	}
	return false;
}
void EnemyChoice::handleMove(const sf::Vector2f& location)
{
	// mark/unmark buttons
	for (auto& item : m_choices)
	{
		(item.first.getGlobalBounds().contains(location)) ? mark(item.first) : unmark(item.first);
	}
}

void EnemyChoice::mark(sf::Text& text)
{
	text.setOutlineColor(sf::Color::Yellow);
	text.setOutlineThickness(BOLD_OUTLINE);
}

void EnemyChoice::unmark(sf::Text& text)
{
	text.setOutlineColor(sf::Color::Transparent);
	text.setOutlineThickness(BOLD_OUTLINE);
}

void noEnemies(sf::RenderWindow&, Arena&) //do nothing
{
}

void withEnemies(sf::RenderWindow& window, Arena& arena) //activate choose enemy difficulty
{
	ChooseDifficulty nextWindow;
	nextWindow.activateChooseDifficulty(window, arena);
}
