#pragma once
#include "Animation.h"
#include "ResourcesManager.h"

class GameObject
{
public:
	GameObject(const sf::Vector2f&);
	virtual ~GameObject() = default;
	virtual void draw(sf::RenderWindow&) ; 

protected:
	sf::Sprite m_picture;
	//Animation m_animation;
private:

};

