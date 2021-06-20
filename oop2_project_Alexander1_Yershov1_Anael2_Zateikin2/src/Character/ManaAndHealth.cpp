#include "Character/ManaAndHealth.h"

const float INCREASE_RATE = 10.f;

ManaAndHealth::ManaAndHealth()
{
	//set the values
	m_healthBar.value = MAX_HEALTH;
	m_manaBar.value = MAX_MANA;

	//set the rectangle
	m_healthBar.rectangles.first.setSize({ BAR_WIDTH, BAR_HEIGHT });
	m_healthBar.rectangles.second.setSize({ BAR_WIDTH, BAR_HEIGHT });
	m_manaBar.rectangles.first.setSize({ BAR_WIDTH, BAR_HEIGHT });
	m_manaBar.rectangles.second.setSize({ BAR_WIDTH, BAR_HEIGHT });
	//colors
	m_healthBar.rectangles.first.setFillColor(sf::Color(225, 20, 0, 220));
	m_healthBar.rectangles.first.setOutlineColor(sf::Color(0, 0, 0, 100)); //shdow
	m_healthBar.rectangles.first.setOutlineThickness(SHADOW_THICKNESS); //shdow
	m_healthBar.rectangles.second.setFillColor(sf::Color(225, 0, 0, 255));

	m_manaBar.rectangles.first.setFillColor(sf::Color(20, 225, 0, 220));
	m_manaBar.rectangles.first.setOutlineColor(sf::Color(0, 0, 0, 100)); //shdow
	m_manaBar.rectangles.first.setOutlineThickness(SHADOW_THICKNESS); //shdow
	m_manaBar.rectangles.second.setFillColor(sf::Color(0, 225, 0, 255));
}
//
//ManaAndHealth::ManaAndHealth(CharacterType character)
//{
//	//m_charIcon.setTexture(ResourcesManager::instance().)
//}

ManaAndHealth::~ManaAndHealth()
{
}

void ManaAndHealth::draw(sf::RenderWindow& window) const
{
	window.draw(m_healthBar.rectangles.first);
	window.draw(m_healthBar.rectangles.second);
	window.draw(m_manaBar.rectangles.first);
	window.draw(m_manaBar.rectangles.second);
}

void ManaAndHealth::increaseMana(const sf::Time& deltaTime)
{
	//m_manaBar.value += deltaTime.asSeconds() * INCREASE_RATE;
	m_manaBar.update(deltaTime.asSeconds() * INCREASE_RATE, MAX_MANA);
}

void ManaAndHealth::decreaseMana(float value)
{
	//decrease(m_manaBar.value, value);
	m_manaBar.update(-value, MAX_MANA);
	
}

void ManaAndHealth::decreaseHealth(float value)
{
	//decrease(m_healthBar.value, value);
	m_healthBar.update(-value, MAX_HEALTH);
}
void ManaAndHealth::setLocation(int plynum)
{
	static  float sectionWidth = m_charIcon.getGlobalBounds().width + BAR_WIDTH;//+ INNER_VERT_SPACE;
	m_charIcon.setPosition({ float(plynum) * sectionWidth + INNER_VERT_SPACE,
							INNER_HORIZ_SPACE * (plynum/4 +1) });
}
void ManaAndHealth::setIcon(CharacterType character)
{
	m_charIcon.setTexture(ResourcesManager::instance().texture(int(character), int(CharacterAssets::SmallIcon)));
}
float ManaAndHealth::getMana() const
{
	return m_manaBar.value;
}
float ManaAndHealth::getHealth() const
{
	return m_healthBar.value;
}
//
//void ManaAndHealth::decrease(float& bar,float value) 
//{
//	bar -= value;
//	if (bar < 0)
//		bar = 0;	//set to zero
//}
