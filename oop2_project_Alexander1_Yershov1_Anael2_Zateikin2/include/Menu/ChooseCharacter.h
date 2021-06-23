#pragma once
//#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "Menu/GenericMenu.h"
#include "Utillities.h"
#include "Arena.h"
#include "Command.h"
#include <string>
//#include <memory>

class ChooseCharacter : public GenericMenu
{
public:
	ChooseCharacter(); //get textures for thumbnails
	~ChooseCharacter();
	CharacterType getChoice() const;
	void activateChooseCharacter(sf::RenderWindow&, Arena&);
	virtual void draw(sf::RenderWindow&) const;
private:
	std::vector<std::pair<sf::Sprite, CharacterType(*)()>> m_characterThumbnails;
	CharacterType m_choice;

	void modifySprites();
	virtual bool handleClick(const sf::Vector2f&, sf::RenderWindow&, Arena&) ;
	virtual void handleMove(const sf::Vector2f&);
};
CharacterType getAlexName(); //{ return CharacterType::Alex; }
CharacterType getAnaelName(); //{ return CharacterType::Anael; }