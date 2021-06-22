#include "Menu/ConclusionWindow.h"
#include "Arena.h"
#include "RestartExc.h"


ConclusionWindow::ConclusionWindow(bool isWon)
	:GenericMenu()
{
	//header
	m_header.setCharacterSize(HEADER_SIZE);
	isWon ? m_header.setString("STAGE CLEARED") : m_header.setString("STAGE LOST");
	sf::FloatRect textRect = m_header.getLocalBounds();
	m_header.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_header.setPosition(HEADER_POS);

	addText("Thank you for playing");
	addText("Click anywhere to go back");
	setTextsLocations(); //arrange on window
}

ConclusionWindow::~ConclusionWindow()
{
}

void ConclusionWindow::activateConclusionWindow(sf::RenderWindow& window, Arena& arena)
{
	activateWindow(window, arena);
}
void ConclusionWindow::addText(const std::string& str)
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
	m_texts.push_back(text);
}

void ConclusionWindow::draw(sf::RenderWindow& window) const
{
	window.draw(m_background);
	window.draw(m_header);
	for (const auto& item : m_texts)
		window.draw(item);
}

void ConclusionWindow::setTextsLocations()
{
	auto yOffset = WINDOW_HEIGHT / float(m_texts.size() + 1) + 20.f;
	auto offsetScale = 1.f;
	for (auto& item : m_texts)
	{
		item.setPosition({ CENTER.x, yOffset * offsetScale });
		offsetScale++;
	}
}

bool ConclusionWindow::handleClick(const sf::Vector2f& location, sf::RenderWindow& window, Arena& arena)
{
	throw RestartExc{ false };
}