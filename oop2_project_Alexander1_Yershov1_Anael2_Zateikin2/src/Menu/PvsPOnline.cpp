#include "Menu/PvsPOnline.h"

PvsPOnline::PvsPOnline()
{
}

PvsPOnline::~PvsPOnline()
{
}

void PvsPOnline::execute(sf::RenderWindow& window, Arena& arena)
{
	m_chooseModeMenu.activateChooseMode(window, arena);

	m_chooseCharMenu.activateChooseCharacter(window, arena);

	if (arena.getMode() == Mode::Server)
	{
		//choose arena 
		m_chooseArena.activateChooseArena(window, arena);

		//activate arena selection and difficulty +create Enemies
		m_chooseDifficulty.activateChooseDifficulty(window, arena);

		waitForOtherPlayer(window);
	}
	arena.createSocket();
}

void PvsPOnline::waitForOtherPlayer(sf::RenderWindow& window)
{
	sf::Text waiting;
	waiting.setString("Waiting for other player...");
	waiting.setFont(ResourcesManager::instance().font());
	waiting.setColor(sf::Color::Green);
	waiting.setCharacterSize(REG_CHAR_SIZE);
	sf::FloatRect textRect = waiting.getLocalBounds();
	waiting.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	waiting.setOutlineColor(sf::Color::Magenta);
	waiting.setOutlineThickness(OUTLINE_THICKNESS);
	waiting.setPosition(CENTER);

	window.clear(sf::Color::Cyan);
	window.draw(waiting);
	window.display();
}
