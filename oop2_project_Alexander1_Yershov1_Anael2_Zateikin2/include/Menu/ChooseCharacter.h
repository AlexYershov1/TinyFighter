#pragma once
#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "Utillities.h"
#include "Arena.h"
#include "Command.h"
#include <string>
#include <memory>

class ChooseCharacter
{
public:
	ChooseCharacter(); //get textures for thumbnails
	~ChooseCharacter();
	int activateChooseCharacter(sf::RenderWindow&);
private:
	std::vector<std::pair<sf::RectangleShape, void(*)()>> m_characterThumbnails;

	void setLocations();
};
int getAlexName() { return int(CharacterType::Alex); }
int getAnaelName() { return int(CharacterType::Anael); }