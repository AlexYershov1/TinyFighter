#include "Menu/ChooseDifficulty.h"
#include "Arena.h"


ChooseDifficulty::ChooseDifficulty()
	:GenericMenu()
{
	//header
	setHeader("Choose difficulty", HEADER_SIZE);
	/*m_header.setCharacterSize(HEADER_SIZE);
	m_header.setString("Choose difficulty");
	sf::FloatRect textRect = m_header.getLocalBounds();
	m_header.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_header.setPosition(HEADER_POS);*/

	//addText("Easy");
	m_difficulties.push_back(createText("Easy"));
	m_difficulties.push_back(createText("Normal"));
	m_difficulties.push_back(createText("Hard"));
	//addText("Normal");
	//addText("Hard");
	setTextsLocations(); //arrange on window
}

ChooseDifficulty::~ChooseDifficulty()
{
}

int ChooseDifficulty::getChoice() const
{
	return m_choice;
}

void ChooseDifficulty::activateChooseDifficulty(sf::RenderWindow& window, Arena& arena)
{
	activateWindow(window, arena);
}


void ChooseDifficulty::draw(sf::RenderWindow& window) const
{
	window.draw(m_background);
	window.draw(m_header);
	for (const auto& item : m_difficulties)
		window.draw(item);
}

void ChooseDifficulty::setTextsLocations()
{
	auto xOffset = WINDOW_WIDTH /float( m_difficulties.size() + 1);
	auto offsetScale = 1.f;
	for (auto& item : m_difficulties)
	{
		item.setPosition({ xOffset * offsetScale, CENTER.y });
		offsetScale++;
	}
}

bool ChooseDifficulty::handleClick(const sf::Vector2f& location, sf::RenderWindow& window, Arena& arena)
{
	int difficulty = 1;
	for (const auto& text : m_difficulties)
	{
		if (text.getGlobalBounds().contains(location))
		{
			for (int i = 0; i < difficulty * ENEM_DIFFICULTY_CORR; i++)
				arena.createEnemy(CharacterType::Bandit);
			m_choice = difficulty * ENEM_DIFFICULTY_CORR;
			return true;
		}
		difficulty++;
	}
	return false;
}

void ChooseDifficulty::handleMove(const sf::Vector2f& location)
{
	// mark/unmark buttons
	for (auto& text : m_difficulties)
	{
		(text.getGlobalBounds().contains(location)) ? mark(text) : unmark(text);
	}
}

void ChooseDifficulty::mark(sf::Text& text)
{
	text.setOutlineColor(sf::Color::Yellow);
	text.setOutlineThickness(BOLD_OUTLINE);
}

void ChooseDifficulty::unmark(sf::Text& text)
{
	text.setOutlineColor(sf::Color::Transparent);
	text.setOutlineThickness(BOLD_OUTLINE);
}

