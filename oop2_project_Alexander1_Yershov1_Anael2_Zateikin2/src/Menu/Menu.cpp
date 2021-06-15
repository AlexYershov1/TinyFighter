#include "Menu/Menu.h"
#include "Menu/PvsPOnline.h"
#include "Menu/PvsC.h"
#include "Menu/Exit.h"

const sf::Vector2f HEADER_POS = { WINDOW_WIDTH / 2 , 60 };
const sf::Vector2f COMMANDS_POS = { WINDOW_WIDTH / 2 , 110 };
const sf::Vector2f CENTER = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
const float VERTICAL_OFFSET = 110.f;

Menu::Menu()
{
	// intialize header
	this->m_header.setFont(ResourcesManager::instance().font());
	m_header.setStyle(sf::Text::Style::Bold | sf::Text::Style::Italic);
	m_header.setCharacterSize(HEADER_SIZE);
	m_header.setString("Tiny Fighter");
	sf::FloatRect textRect = m_header.getLocalBounds();
	m_header.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_header.setPosition(HEADER_POS);
	m_header.setColor(sf::Color::Magenta);
	m_header.setOutlineColor(sf::Color::Black);
	m_header.setOutlineThickness(OUTLINE_THICKNESS);

	
	//setButton
	/*setButton(m_pVSc, "PVSC_abcdefdf", { CENTER.x , CENTER.y - 120.f });
	setButton(m_pVSp1Keyboard, "PlVSP_fgdgddhdhdf", { CENTER.x , CENTER.y - 40.f });
	setButton(m_pVSpOnline, "PVSP(online)", { CENTER.x , CENTER.y + 40.f });
	setButton(m_exit, "Exit", { CENTER.x , CENTER.y + 120.f });*/
	
	//CHANGE THIS
	this->m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	this->m_background.setTexture(ResourcesManager::instance().texture(ArenaType::Arena1, BackroundAssets::Background));
	
	//add Commands
	addCommand("Player VS Computer", std::make_unique<PvsC>());
	//add Player VS Player
	addCommand("Player VS Player(online)", std::make_unique<PvsPOnline>());
	addCommand("Exit", std::make_unique<Exit>());


}

Menu::~Menu()
{
}

StageInfo Menu::activateMenu(sf::RenderWindow& window, Arena& arena)
{
	auto stageInfo = StageInfo();
	//window loop
	while (window.isOpen() && stageInfo.characterNames.empty())
	{
		window.clear(sf::Color::White);
		draw(window);
		window.display();

		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			sf::Vector2f Location;
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				Location = window.mapPixelToCoords
				({ event.mouseButton.x, event.mouseButton.y });
				//if (handleClick(Location, window)) 
				stageInfo = handleClick(Location, window);
				break;
			case sf::Event::MouseMoved:
				Location = (sf::Vector2f)sf::Mouse::getPosition(window);
				handleMove(Location);
				break;
			}
		}
	}

	return stageInfo;
}

void Menu::draw(sf::RenderWindow& window) const
{
	window.draw(this->m_background);
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

StageInfo Menu::handleClick(const sf::Vector2f& location, sf::RenderWindow& window /*,arena*/) const
{
	//go over all buttons and check if pressed
	for (const auto& button : m_options)
	{
		if (button.first.getGlobalBounds().contains(location))
			return button.second->execute(window); //execute command
	}
	return StageInfo();
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
	
	//if (this->m_pVSc.getGlobalBounds().contains(location))
	//{
	//	this->m_pVSc.setOutlineColor(sf::Color::Red);
	//	this->m_pVSc.setOutlineThickness(BOLD_OUTLINE);
	//}
	//else
	//{
	//	this->m_pVSc.setOutlineColor(sf::Color::Magenta);
	//	this->m_pVSc.setOutlineThickness(OUTLINE_THICKNESS);
	//}
	//// mark/unmark exit button
	//if (this->m_exit.getGlobalBounds().contains(location))
	//{
	//	this->m_exit.setOutlineColor(sf::Color::Red);
	//	this->m_exit.setOutlineThickness(BOLD_OUTLINE);
	//}
	//else
	//{
	//	this->m_exit.setOutlineColor(sf::Color::Magenta);
	//	this->m_exit.setOutlineThickness(OUTLINE_THICKNESS);
	//}
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
	/*
	if (button.getTransform() == sf::Transform())
		throw("Anaels' computer sucks");
		*/
}
