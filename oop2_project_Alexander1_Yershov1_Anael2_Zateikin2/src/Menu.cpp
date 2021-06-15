#include "Menu.h"

const sf::Vector2f HEADER_POS = { WINDOW_WIDTH / 2 - 330, 10 };
const sf::Vector2f CENTER = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
const sf::Vector2f RECT_SIZE = { 140.0, 60.0 };


Menu::Menu()
{
	// intialize header
	this->m_header.setFont(ResourcesManager::instance().font());
	m_header.setStyle(sf::Text::Style::Bold | sf::Text::Style::Italic);
	m_header.setCharacterSize(HEADER_SIZE);
	m_header.setPosition(HEADER_POS);
	m_header.setString("Tiny Fighter");
	m_header.setColor(sf::Color::Magenta);
	m_header.setOutlineColor(sf::Color::Black);
	m_header.setOutlineThickness(OUTLINE_THICKNESS);

	
	//setButton
	setButton(m_pVSc, "PVSC_avavavava", { CENTER.x , CENTER.y - 120.f });
	setButton(m_pVSp1Keyboard, "PlVSP_abababab", { CENTER.x , CENTER.y - 40.f });
	setButton(m_pVSpOnline, "PVSP(online)_ababab", { CENTER.x , CENTER.y + 40.f });
	setButton(m_exit, "Exit", { CENTER.x , CENTER.y + 120.f });
	
	/*
	// intialize "Player VS Computer" button
	this->m_pVSc.setFont(ResourcesManager::instance().font());
	m_pVSc.setColor(sf::Color::Green);
	m_pVSc.setCharacterSize(REG_CHAR_SIZE);
	m_pVSc.setPosition({ CENTER.x , CENTER.y - 60.f});
	m_pVSc.setString("Player VS Computer");
	m_pVSc.setOutlineColor(sf::Color::Magenta);
	m_pVSc.setOutlineThickness(OUTLINE_THICKNESS);

	// intialize "Player VS Player" button
	this->m_pVSp1Keyboard.setFont(ResourcesManager::instance().font());
	m_pVSp1Keyboard.setColor(sf::Color::Green);
	m_pVSp1Keyboard.setCharacterSize(REG_CHAR_SIZE);
	m_pVSp1Keyboard.setPosition({ CENTER.x , CENTER.y - 20.f });
	m_pVSp1Keyboard.setString("Player VS Player");
	m_pVSp1Keyboard.setOutlineColor(sf::Color::Magenta);
	m_pVSp1Keyboard.setOutlineThickness(OUTLINE_THICKNESS);

	// intialize "Player VS Player(online)" button
	this->m_pVSpOnline.setFont(ResourcesManager::instance().font());
	m_pVSpOnline.setColor(sf::Color::Green);
	m_pVSpOnline.setCharacterSize(REG_CHAR_SIZE);
	m_pVSpOnline.setPosition({ CENTER.x, CENTER.y + 20.f });
	m_pVSpOnline.setString("Player VS Player(online)");
	m_pVSpOnline.setOutlineColor(sf::Color::Magenta);
	m_pVSpOnline.setOutlineThickness(OUTLINE_THICKNESS);

	// intialize "Player VS Player(online)" button
	this->m_exit.setFont(ResourcesManager::instance().font());
	m_exit.setColor(sf::Color::Green);
	m_exit.setCharacterSize(REG_CHAR_SIZE);
	m_exit.setPosition({ CENTER.x, CENTER.y + 60.f});
	m_exit.setString("Exit");
	m_exit.setOutlineColor(sf::Color::Magenta);
	m_exit.setOutlineThickness(OUTLINE_THICKNESS);
	*/
	
	//CHANGE THIS
	this->m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	this->m_background.setTexture(ResourcesManager::instance().texture(ArenaType::Arena1, BackroundAssets::Background));
}

Menu::~Menu()
{
}

void Menu::activateMenu(sf::RenderWindow& window, Arena& arena)
{
	//window loop
	while (window.isOpen())
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
				if (handleClick(Location, window)) 
					//activate chooseCharacterMenu
					return;
				break;
			case sf::Event::MouseMoved:
				Location = (sf::Vector2f)sf::Mouse::getPosition(window);
				handleMove(Location);
				break;
			}
		}
	}

	//return StageInfo();
}

void Menu::draw(sf::RenderWindow& window) const
{
	window.draw(this->m_background);
	window.draw(this->m_header);
	window.draw(this->m_pVSc);
	window.draw(this->m_pVSp1Keyboard);
	window.draw(this->m_pVSpOnline);
	window.draw(this->m_exit);
}

bool Menu::handleClick(const sf::Vector2f& location, sf::RenderWindow& window) const
{
	if (this->m_pVSc.getGlobalBounds().contains(location)) // pressed Player Vs Computer
	{
		//activate Choose Chracter
		return true;
	}
		
	if (this->m_exit.getGlobalBounds().contains(location))
		window.close();
	return false;
}

void Menu::handleMove(const sf::Vector2f& location)
{
	// mark/unmark start button
	if (this->m_pVSc.getGlobalBounds().contains(location))
	{
		this->m_pVSc.setOutlineColor(sf::Color::Red);
		this->m_pVSc.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_pVSc.setOutlineColor(sf::Color::Magenta);
		this->m_pVSc.setOutlineThickness(OUTLINE_THICKNESS);
	}
	// mark/unmark exit button
	if (this->m_exit.getGlobalBounds().contains(location))
	{
		this->m_exit.setOutlineColor(sf::Color::Red);
		this->m_exit.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_exit.setOutlineColor(sf::Color::Magenta);
		this->m_exit.setOutlineThickness(OUTLINE_THICKNESS);
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
	//button.setOrigin(button.getLocalBounds().height / 2, button.getLocalBounds().width / 2);
	button.setPosition(location);
	button.setOutlineColor(sf::Color::Magenta);
	button.setOutlineThickness(OUTLINE_THICKNESS);
	//button.setOrigin(button.getLocalBounds().height / 2, button.getLocalBounds().width / 2);
}
