#include "StatesSection.h"


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
