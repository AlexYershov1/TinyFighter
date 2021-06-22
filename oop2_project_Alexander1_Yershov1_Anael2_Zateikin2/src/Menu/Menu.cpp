#include "Menu/Menu.h"
#include "Menu/PvsPOnline.h"
#include "Menu/PvsC.h"
#include "Menu/Exit.h"



Menu::Menu()
{
	// intialize header
	/*this->m_header.setFont(ResourcesManager::instance().font());
	m_header.setStyle(sf::Text::Style::Bold | sf::Text::Style::Italic);*/
	m_header.setCharacterSize(HEADER_SIZE);
	m_header.setString("Tiny Fighter");
	sf::FloatRect textRect = m_header.getLocalBounds();
	m_header.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_header.setPosition(HEADER_POS);
	
	//add Commands
	addCommand("Player VS Computer", std::make_unique<PvsC>());
	//add Player VS Player
	addCommand("Player VS Player(online)", std::make_unique<PvsPOnline>());
	addCommand("Exit", std::make_unique<Exit>());


}

Menu::~Menu()
{
}

void Menu::activateMenu(sf::RenderWindow& window, Arena& arena)
{
	//window loop
	GenericMenu::activateWindow(window, arena);
	
}

void Menu::draw(sf::RenderWindow& window) const
{
	window.draw(m_background);
	window.draw(this->m_header);
	for (const auto& button : m_options)
		window.draw(button.first);
}

void Menu::addCommand(const std::string& str, std::unique_ptr<Command> command)
{
	//set string, give location according to vector
	sf::Text text;
	setButton(text, str, { COMMANDS_POS.x , COMMANDS_POS.y + HEADER_POS.y +VERTICAL_OFFSET*(m_options.size()) });
	m_options.push_back(option(text, std::move(command)));
}

bool Menu::handleClick(const sf::Vector2f& location, sf::RenderWindow& window ,Arena& arena) 
{
	//go over all buttons and check if pressed
	for (const auto& button : m_options)
	{
		if (button.first.getGlobalBounds().contains(location))
		{
			button.second->execute(window, arena); //execute command
			return true;
		}
	}
	return false;
}

void Menu::handleMove(const sf::Vector2f& location)
{
	// mark/unmark buttons
	for (auto& button : m_options)
	{
		if (button.first.getGlobalBounds().contains(location))
		{
			button.first.setOutlineColor(sf::Color::Red);
			button.first.setOutlineThickness(BOLD_OUTLINE);
		}
		else
		{
			button.first.setOutlineColor(sf::Color::Magenta);
			button.first.setOutlineThickness(BOLD_OUTLINE);
		}
			
	}
	
	
}


void Menu::setButton(sf::Text& button, const std::string& str, const sf::Vector2f& location)
{
	button.setFont(ResourcesManager::instance().font());
	button.setColor(sf::Color::Green);
	button.setCharacterSize(REG_CHAR_SIZE);
	button.setString(str);
	sf::FloatRect textRect = button.getLocalBounds();
	button.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	button.setPosition(location);
	button.setOutlineColor(sf::Color::Magenta);
	button.setOutlineThickness(OUTLINE_THICKNESS);
	
}
