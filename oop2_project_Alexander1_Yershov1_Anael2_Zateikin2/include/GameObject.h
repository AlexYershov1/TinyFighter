#pragma once
#include "Animation.h"
#include "ResourcesManager.h"
#include "Utillities.h"

class GameObject
{
public:
	GameObject(const sf::Vector2f&);
	virtual ~GameObject() = default;
	virtual void draw(sf::RenderWindow&) ; 
	virtual void move(const sf::Time&) = 0;
	virtual void update(const sf::Time&) = 0;

	bool collidesWith(const GameObject&) const;

protected:
	sf::Sprite m_picture;
	Action m_action;
	//Animation m_animation;
private:

};

