#include "Character/ManaAndHealth.h"
#include "StatesSection.h"

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
	m_healthBar.rectangles.first.setFillColor(sf::Color(168, 65, 65, 220));
	m_healthBar.rectangles.first.setOutlineColor(sf::Color(0, 0, 0, 100)); //shdow
	m_healthBar.rectangles.first.setOutlineThickness(SHADOW_THICKNESS); //shdow
	m_healthBar.rectangles.second.setFillColor(sf::Color(225, 0, 0, 255));

	m_manaBar.rectangles.first.setFillColor(sf::Color(20, 0, 225, 220));
	m_manaBar.rectangles.first.setOutlineColor(sf::Color(0, 0, 0, 100)); //shdow
	m_manaBar.rectangles.first.setOutlineThickness(SHADOW_THICKNESS); //shdow
	m_manaBar.rectangles.second.setFillColor(sf::Color(20, 150, 150, 255));
}

ManaAndHealth::~ManaAndHealth()
{
}

void ManaAndHealth::draw(sf::RenderWindow& window) const
{
	window.draw(m_charIcon);
	window.draw(m_healthBar.rectangles.first);
	window.draw(m_healthBar.rectangles.second);
	window.draw(m_manaBar.rectangles.first);
	window.draw(m_manaBar.rectangles.second);
}

void ManaAndHealth::move()
{
	setPositions(); //move along with the view
}

void ManaAndHealth::increaseMana(const sf::Time& deltaTime)
{
	m_manaBar.update(deltaTime.asSeconds() * INCREASE_RATE, MAX_MANA);
}

void ManaAndHealth::decreaseMana(float value)
{
	m_manaBar.update(-value, MAX_MANA);	
}

void ManaAndHealth::decreaseMana(ActionType type)
{
	//distinguish dynamic from static
	if (type == ActionType::SpecialDynamic)  
		decreaseMana(SPECIAL_DINAM_MANA);

	else if (type == ActionType::SpecialStatic)
		decreaseMana(SPECIAL_STATIC_MANA);
}

bool ManaAndHealth::decreaseHealth(float value)
{
	m_healthBar.update(-value, MAX_HEALTH);
	if (m_healthBar.value <= 0)
	{
		if (m_fading.getElapsedTime() > FADING_TIME + SPECIAL_DELAY)
			m_fading.restart();
		return false; // dead
	}
	return true; // still alive
}

void ManaAndHealth::setLocation(int plynum)
{
	static  float sectionWidth = m_charIcon.getGlobalBounds().width + BAR_WIDTH + INNER_VERT_SPACE;
	m_blockOffset = { float(plynum) * sectionWidth,float(plynum / 4) * BAR_HEIGHT };

	setPositions(); //set The inner rectangles positions
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
bool ManaAndHealth::isFaded() const
{
	return m_fading.getElapsedTime() > FADING_TIME;
}
void ManaAndHealth::setPositions()
{
	auto viewOffset = StatesSection::getRlativeStart();
	auto iconWidth = m_charIcon.getGlobalBounds().width;
	auto xBarsPos = m_blockOffset.x + iconWidth + viewOffset.x;

	m_charIcon.setPosition(m_blockOffset + viewOffset);
	m_healthBar.rectangles.first.setPosition(xBarsPos, m_blockOffset.y + viewOffset.y);
	m_healthBar.rectangles.second.setPosition(xBarsPos, m_blockOffset.y + viewOffset.y);
	m_manaBar.rectangles.first.setPosition(xBarsPos, m_blockOffset.y+BAR_HEIGHT + viewOffset.y);
	m_manaBar.rectangles.second.setPosition(xBarsPos, m_blockOffset.y + BAR_HEIGHT + viewOffset.y);
}
