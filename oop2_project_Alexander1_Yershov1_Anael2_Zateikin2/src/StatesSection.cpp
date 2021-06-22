#include "StatesSection.h"

sf::Vector2f StatesSection::m_relativeStarPos = { 0 ,0};

StatesSection::StatesSection()
{
	m_template.setSize({ WINDOW_WIDTH, CAPTION_HEIGHT });
	m_template.setFillColor(sf::Color(50, 10, 200, 225));
	m_template.setPosition(0, 0);
}

StatesSection::~StatesSection()
{
}

void StatesSection::draw(sf::RenderWindow& window) const
{
	window.draw(m_template);
}

void StatesSection::move()
{
	m_template.setPosition(m_relativeStarPos);
}

void StatesSection::setRelativeStart(sf::Vector2f newStart)
{
	m_relativeStarPos = newStart;
}

sf::Vector2f StatesSection::getRlativeStart()
{
	return m_relativeStarPos;
}
