#include "Menu/ChooseMode.h"
#include "Arena.h"
#include "RestartExc.h"


ChooseMode::ChooseMode()
	:GenericMenu()
{
	//header
	m_header.setCharacterSize(HEADER_SIZE);
	m_header.setString("Choose Mode");
	sf::FloatRect textRect = m_header.getLocalBounds();
	m_header.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_header.setPosition(HEADER_POS);

	addText("Create Game");
	addText("Join Game");
	addText("Back To Menu");
	setTextsLocations(); //arrange on window
}

ChooseMode::~ChooseMode()
{
}

void ChooseMode::activateChooseMode(sf::RenderWindow& window, Arena& arena)
{
	activateWindow(window, arena);
}
void ChooseMode::addText(const std::string& str)
{
	//set string, give location according to vector
	sf::Text text;
	text.setFont(ResourcesManager::instance().font());
	text.setColor(sf::Color::Green);
	text.setCharacterSize(REG_CHAR_SIZE);
	text.setString(str);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	//text.setPosition(location);
	text.setOutlineColor(sf::Color::Magenta);
	text.setOutlineThickness(OUTLINE_THICKNESS);
	m_options.push_back(text);
}

void ChooseMode::draw(sf::RenderWindow& window) const
{
	window.draw(m_background);
	window.draw(m_header);
	for (const auto& item : m_options)
		window.draw(item);
}

void ChooseMode::setTextsLocations()
{
	auto yOffset = WINDOW_HEIGHT / float(m_options.size() + 1) + 20.f;
	auto offsetScale = 1.f;
	for (auto& item : m_options)
	{
		item.setPosition({ CENTER.x, yOffset * offsetScale });
		offsetScale++;
	}
}

bool ChooseMode::handleClick(const sf::Vector2f& location, sf::RenderWindow& window, Arena& arena)
{
	for (const auto& text : m_options)
	{
		if (text.getGlobalBounds().contains(location))
		{
			if (text.getString() == "Create Game")
				arena.setMode(Mode::Server);
			if (text.getString() == "Join Game")
				arena.setMode(Mode::Client);
			if (text.getString() == "Back To Menu")
				throw RestartExc{ true };
			return true;
		}
	}
	return false;
}

void ChooseMode::handleMove(const sf::Vector2f& location)
{
	// mark/unmark buttons
	for (auto& text : m_options)
	{
		(text.getGlobalBounds().contains(location)) ? mark(text) : unmark(text);
	}
}

void ChooseMode::mark(sf::Text& text)
{
	text.setOutlineColor(sf::Color::Yellow);
	text.setOutlineThickness(BOLD_OUTLINE);
}

void ChooseMode::unmark(sf::Text& text)
{
	text.setOutlineColor(sf::Color::Transparent);
	text.setOutlineThickness(BOLD_OUTLINE);
}