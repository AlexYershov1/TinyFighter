#include "Menu/GenericMenu.h"


GenericMenu::GenericMenu()
{
	//background
	m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	m_background.setTexture(ResourcesManager::instance().menuBGTexture());
	
	//header
	this->m_header.setFont(ResourcesManager::instance().font());
	m_header.setStyle(sf::Text::Style::Bold | sf::Text::Style::Italic);
	m_header.setColor(sf::Color::Magenta);
	m_header.setOutlineColor(sf::Color::Black);
	m_header.setOutlineThickness(OUTLINE_THICKNESS);
}

GenericMenu::~GenericMenu()
{
}

void GenericMenu::draw(sf::RenderWindow& window) const
{
	window.draw(m_background);
	window.draw(m_header);

}

void GenericMenu::activateWindow(sf::RenderWindow& window, Arena& arena)
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
				if (handleClick(Location, window, arena))
					return;
				break;
			case sf::Event::MouseMoved:
				Location = (sf::Vector2f)sf::Mouse::getPosition(window);
				handleMove(Location);
				break;
			}
		}
	}
}

void GenericMenu::setBackground(sf::Texture* texutrePtr)
{
	m_background.setTexture(texutrePtr);
}
void GenericMenu::setHeader(const std::string& str, float charSize)
{
	m_header.setCharacterSize(charSize);
	m_header.setString(str);
	sf::FloatRect textRect = m_header.getLocalBounds();
	m_header.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_header.setPosition(HEADER_POS);

}
//This function receives a string and returns a modified text
sf::Text GenericMenu::createText(const std::string& str) const
{
	//set string, give location according to vector
	sf::Text text;
	text.setFont(ResourcesManager::instance().font());
	text.setColor(sf::Color::Green);
	text.setCharacterSize(REG_CHAR_SIZE);
	text.setString(str);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setOutlineColor(sf::Color::Magenta);
	text.setOutlineThickness(OUTLINE_THICKNESS);
	return text;
}

