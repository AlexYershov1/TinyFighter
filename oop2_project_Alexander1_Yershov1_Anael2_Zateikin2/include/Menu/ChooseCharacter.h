#pragma once
//#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "Utillities.h"
#include "Arena.h"
#include "Command.h"
#include <string>
//#include <memory>

class ChooseCharacter
{
public:
	ChooseCharacter(); //get textures for thumbnails
	~ChooseCharacter();
	void activateChooseCharacter(sf::RenderWindow&, Arena&);
	void draw(sf::RenderWindow&) const;
private:
	std::vector<std::pair<sf::Sprite, CharacterType(*)()>> m_characterThumbnails;

	void modifySprites();
	bool handleClick(const sf::Vector2f&, Arena&) const;
	void handleMove(const sf::Vector2f& location);
};
CharacterType getAlexName(); //{ return CharacterType::Alex; }
CharacterType getAnaelName(); //{ return CharacterType::Anael; }