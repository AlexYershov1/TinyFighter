#include "Menu/PvsPOnline.h"

PvsPOnline::PvsPOnline()
{
}

PvsPOnline::~PvsPOnline()
{
}

void PvsPOnline::execute(sf::RenderWindow& window, Arena& arena)
{
	InitialServerInfo serverInfo;
	CharacterType clientInfo;

	m_chooseModeMenu.activateChooseMode(window, arena);

	m_chooseCharMenu.activateChooseCharacter(window, arena);

	if (arena.getMode() == Mode::Server)
	{
		//choose arena
		m_chooseArena.activateChooseArena(window, arena);

		//activate arena selection and difficulty +create Enemies
		m_chooseDifficulty.activateChooseDifficulty(window, arena);

		serverInfo.m_arena = m_chooseArena.getChoice();
		serverInfo.m_character = m_chooseCharMenu.getChoice();
		serverInfo.m_difficulty = m_chooseDifficulty.getChoice();

		waitForOtherPlayer(window);
	}
	arena.createSocket();
	if (arena.getMode() == Mode::Server)
	{
		
		clientInfo = receive<CharacterType>();
		sending(serverInfo);
		arena.createPlayer(clientInfo, true);
	}
	if (arena.getMode() == Mode::Client)
	{
		clientInfo = m_chooseCharMenu.getChoice();
		sending(clientInfo);
		serverInfo = receive<InitialServerInfo>();
		
		arena.createPlayer(serverInfo.m_character, true);
		arena.setArenaBackground(serverInfo.m_arena);
		for (int i = 0; i < serverInfo.m_difficulty; i++)
			arena.createEnemy(CharacterType::Bandit);
	}

	
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
