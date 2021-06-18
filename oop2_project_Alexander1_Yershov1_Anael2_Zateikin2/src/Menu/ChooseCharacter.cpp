#include "Menu/ChooseCharacter.h"


ChooseCharacter::ChooseCharacter()
	//: m_characterThumbnails(int(CharacterType::Bandit))
{
	sf::Sprite charSprite;
	//character.setTexture(ResourcesManager::instance())		//load thumbnail
	charSprite.setTexture(ResourcesManager::instance().texture(int(CharacterType::Alex), THUMBNAIL));
	m_characterThumbnails.emplace_back(charSprite, getAlexName);
	charSprite.setTexture(ResourcesManager::instance().texture(int(CharacterType::Anael), THUMBNAIL));
	m_characterThumbnails.emplace_back(charSprite, getAnaelName);
	//set locations for rects
	modifySprites();


}

ChooseCharacter::~ChooseCharacter()
{
}

void ChooseCharacter::activateChooseCharacter(sf::RenderWindow& window, Arena& arena)
{
	GenericMenu::activateWindow(window, arena);
	//background
	/*sf::RectangleShape background;
	background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
	background.setTexture(ResourcesManager::instance().menuBGTexture());*/
	//window loop
	/*while (window.isOpen())
	{
		window.clear(sf::Color::White);
		window.draw(background);
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
				if (handleClick(Location, arena))
					return ;
				break;
			case sf::Event::MouseMoved:
				Location = (sf::Vector2f)sf::Mouse::getPosition(window);
				handleMove(Location);
				break;
			}
		}
	}*/

}

void ChooseCharacter::draw(sf::RenderWindow& window) const
{
	for (const auto& item : m_characterThumbnails)
		window.draw(item.first);
}

void ChooseCharacter::modifySprites()
{
	auto xOffset = WINDOW_WIDTH / 3.f;
	auto offsetScale = 1;
	for (auto& item : m_characterThumbnails)
	{
		item.first.setOrigin(item.first.getLocalBounds().height / 2,
							 item.first.getLocalBounds().width / 2);
		item.first.setPosition({ xOffset * offsetScale, CENTER.y });
		offsetScale++;
	}
}

bool ChooseCharacter::handleClick(const sf::Vector2f& location, sf::RenderWindow&, Arena& arena)
{
	//go over all buttons and check if pressed
	for (const auto& button : m_characterThumbnails)
	{
		if (button.first.getGlobalBounds().contains(location))
		{
			arena.createPlayer(button.second());
			return true;
		}	
	}
	return false;
}

void ChooseCharacter::handleMove(const sf::Vector2f& location)
{
	// mark/unmark buttons
	for (auto& button : m_characterThumbnails)
	{
		if (button.first.getGlobalBounds().contains(location))
		{
			button.first.setColor(sf::Color(225, 225, 225, 125));
			//button.first.setOutlineThickness(BOLD_OUTLINE);
		}
		else
		{
			//button.first.
			button.first.setColor(sf::Color(225, 225, 225, 225));
			//button.first.setOutlineThickness(BOLD_OUTLINE);
		}
	}
}

CharacterType getAlexName()
{
	return CharacterType::Alex;
}

CharacterType getAnaelName()
{
	return CharacterType::Anael;
}
