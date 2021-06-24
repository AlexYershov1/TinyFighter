#include "Menu/InstructionsWindow.h"

InstructionsWindow::InstructionsWindow()
	:GenericMenu()
{
	//header
	m_header.setCharacterSize(HEADER_SIZE);
	m_header.setString("Instructions");
	sf::FloatRect textRect = m_header.getLocalBounds();
	m_header.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_header.setPosition(HEADER_POS);

	auto startX = 150.f, startY = 250.f, distance = 450.f;

	addText("Player 1", sf::Vector2f{ startX, startX });
	addText("Player 2", sf::Vector2f{ startX + distance, startX });
	addText("Click anywhere to continue", sf::Vector2f{ CENTER.x, CENTER.y + startY });
	addText("sprint-R shift", sf::Vector2f{ CENTER.x - startY, CENTER.y + startX });
	addText("Sprint- space", sf::Vector2f{ CENTER.x + startY - ADJUST, CENTER.y + startX});

	sf::Sprite icon;
	icon.setTexture(*ResourcesManager::instance().texture(Buttons::Arrows));
	m_buttons.emplace_back(icon);
	icon.setTexture(*ResourcesManager::instance().texture(Buttons::I));
	m_buttons.emplace_back(icon);
	icon.setTexture(*ResourcesManager::instance().texture(Buttons::O));
	m_buttons.emplace_back(icon);
	icon.setTexture(*ResourcesManager::instance().texture(Buttons::P));
	m_buttons.emplace_back(icon);
	icon.setTexture(*ResourcesManager::instance().texture(Buttons::WASD));
	m_buttons.emplace_back(icon);
	icon.setTexture(*ResourcesManager::instance().texture(Buttons::C));
	m_buttons.emplace_back(icon);
	icon.setTexture(*ResourcesManager::instance().texture(Buttons::V));
	m_buttons.emplace_back(icon);
	icon.setTexture(*ResourcesManager::instance().texture(Buttons::B));
	m_buttons.emplace_back(icon);
	modifyButtons(startX, 0);

	modifyButtons(startX + distance, (int)Buttons::P);
}

InstructionsWindow::~InstructionsWindow()
{
}

void InstructionsWindow::activateInstructionsWindow(sf::RenderWindow& window, Arena& arena)
{
	activateWindow(window, arena);
}

void InstructionsWindow::addText(const std::string& str, sf::Vector2f location)
{
	//set string, give location according to vector
	sf::Text text;
	text.setFont(ResourcesManager::instance().font());
	text.setColor(sf::Color::Green);
	text.setCharacterSize(REG_CHAR_SIZE);
	text.setString(str);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(location);
	text.setOutlineColor(sf::Color::Magenta);
	text.setOutlineThickness(OUTLINE_THICKNESS);
	m_texts.push_back(text);
}

void InstructionsWindow::modifyButtons(float OFFSET, int start)
{
	auto xOffset = WINDOW_WIDTH / float(m_buttons.size() + 1);
	auto offsetScale = 1.f;

	m_buttons[start].setOrigin(m_buttons[start].getLocalBounds().height / 2,
		m_buttons[start].getLocalBounds().width / 2);
	m_buttons[start].setScale(0.25, 0.25);
	m_buttons[start].setPosition({ OFFSET, CENTER.y });
	start++;
	auto mildOffset = 0.f;

	for (auto i = 0; i < BUTTONS_ON_SIDE; i++)
	{
		m_buttons[start].setOrigin(m_buttons[start].getLocalBounds().height / 2,
			m_buttons[start].getLocalBounds().width / 2);
		m_buttons[start].setScale(0.1, 0.1);
		m_buttons[start].setPosition({ OFFSET - ADJUST + mildOffset, CENTER.y + ADJUST*2 });
		offsetScale++;
		start++;
		mildOffset += ADJUST;
	}
}

void InstructionsWindow::draw(sf::RenderWindow& window) const
{
	window.draw(m_background);
	window.draw(m_header);
	for (const auto& item : m_texts)
		window.draw(item);
	for (const auto& item : m_buttons)
		window.draw(item);
}

bool InstructionsWindow::handleClick(const sf::Vector2f& location, sf::RenderWindow& window, Arena& arena)
{
	return true;
}
