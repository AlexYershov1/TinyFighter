#include "Menu/ChooseCharacter.h"


ChooseCharacter::ChooseCharacter()
	: GenericMenu()
{
	sf::Sprite charSprite;
	//load thumbnail
	charSprite.setTexture(ResourcesManager::instance().texture(int(CharacterType::Alex), THUMBNAIL));
	m_characterThumbnails.emplace_back(charSprite, getAlexName);
	charSprite.setTexture(ResourcesManager::instance().texture(int(CharacterType::Anael), THUMBNAIL));
	m_characterThumbnails.emplace_back(charSprite, getAnaelName);

	//set locations for rects
	modifySprites();
	
	//header
	setHeader("Choose your character", HEADER_SIZE - 20);
	/*m_header.setCharacterSize(HEADER_SIZE- 20);
	m_header.setString("Choose your character");
	sf::FloatRect textRect = m_header.getLocalBounds();
	m_header.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_header.setPosition(HEADER_POS);*/


}

ChooseCharacter::~ChooseCharacter()
{
}

void ChooseCharacter::activateChooseCharacter(sf::RenderWindow& window, Arena& arena)
{
	GenericMenu::activateWindow(window, arena);
}

void ChooseCharacter::draw(sf::RenderWindow& window) const
{
	window.draw(m_background);
	window.draw(m_header);
	for (const auto& item : m_characterThumbnails)
		window.draw(item.first);
}

void ChooseCharacter::modifySprites()
{
	auto xOffset = WINDOW_WIDTH / float(m_characterThumbnails.size() + 1);
	auto offsetScale = 1.f;
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
