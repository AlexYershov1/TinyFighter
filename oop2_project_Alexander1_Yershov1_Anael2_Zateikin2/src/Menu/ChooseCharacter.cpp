#include "Menu/ChooseCharacter.h"


ChooseCharacter::ChooseCharacter()
	//: m_characterThumbnails(int(CharacterType::Bandit))
{
	sf::RectangleShape charRect;
	//character.setTexture(ResourcesManager::instance())		//load thumbnail
	charRect.setFillColor(sf::Color::Red);
	m_characterThumbnails.emplace_back(charRect, getAlexName);
	charRect.setFillColor(sf::Color::Blue);
	m_characterThumbnails.emplace_back(charRect, getAnaelName);
	//set locations for rects
	setLocations();
}

ChooseCharacter::~ChooseCharacter()
{
}

int ChooseCharacter::activateChooseCharacter(sf::RenderWindow&)
{
	//window loop
	
	//return std::string();
}

void ChooseCharacter::setLocations()
{

}
