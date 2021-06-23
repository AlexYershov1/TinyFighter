#pragma once
#include "Animation.h"
#include "ResourcesManager.h"
#include "Utillities.h"

class Arena;

class GameObject
{
public:
	GameObject(const sf::Vector2f&);
	virtual ~GameObject() = default;
	virtual void draw(sf::RenderWindow&) const ; 
	virtual void move(const sf::Time&, Arena&) = 0;
	virtual void update(const sf::Time&) = 0;
	virtual void correctOwnersPtr() = 0;
	bool isAlive() const;
	virtual bool isFaded() = 0;
	void switchPic(GameObject*);

	bool collidesWith(const GameObject&) const;
	float y() const;
	sf::Vector2f getLocation() const;
protected:
	sf::Sprite m_picture;
	Action m_action;
	bool m_alive;
	float m_speed;
	//Animation m_animation;
private:

};

