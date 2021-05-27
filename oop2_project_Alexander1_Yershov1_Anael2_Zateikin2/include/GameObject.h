#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject(const sf::Vector2f&);
	virtual ~GameObject();
	virtual void draw(sf::RenderWindow&) ; 

private:
	sf::Sprite m_picture;
};

