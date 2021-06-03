#pragma once
#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f& loc)
{
	m_picture.setPosition(loc);
}

GameObject::~GameObject()
{
}

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(m_picture);
}
