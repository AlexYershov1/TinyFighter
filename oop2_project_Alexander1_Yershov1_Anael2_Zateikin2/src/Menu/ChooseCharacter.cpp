#include "Menu/ChooseCharacter.h"
#include "Menu/InstructionsWindow.h"

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
}

ChooseCharacter::~ChooseCharacter()
{
}

CharacterType ChooseCharacter::getChoice() const
{
	return m_choice;
}

void ChooseCharacter::addSecondHeader(const std::string& str)
{
	m_secondHeader.setFont(ResourcesManager::instance().font());
	m_secondHeader.setStyle(sf::Text::Style::Bold | sf::Text::Style::Italic);
	m_secondHeader.setColor(sf::Color::Magenta);
	m_secondHeader.setOutlineColor(sf::Color::Black);
	m_secondHeader.setOutlineThickness(OUTLINE_THICKNESS);
	m_secondHeader.setCharacterSize(REG_CHAR_SIZE);
	m_secondHeader.setString(str);
	sf::FloatRect textRect = m_secondHeader.getLocalBounds();
	m_secondHeader.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_secondHeader.setPosition({ HEADER_POS.x, HEADER_POS.y + HEADER_SIZE });

}

void ChooseCharacter::setSecondHeader(const std::string& str)
{
	m_secondHeader.setString(str);
}

void ChooseCharacter::activateChooseCharacter(sf::RenderWindow& window, Arena& arena)
{
	// showing instructions before picking a character
	InstructionsWindow inst;
	inst.activateInstructionsWindow(window, arena);

	GenericMenu::activateWindow(window, arena);
}

void ChooseCharacter::draw(sf::RenderWindow& window) const
{
	window.draw(m_background);
	window.draw(m_header);
	window.draw(m_secondHeader);
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
			m_choice = button.second();
			arena.createPlayer(button.second(), false);
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
