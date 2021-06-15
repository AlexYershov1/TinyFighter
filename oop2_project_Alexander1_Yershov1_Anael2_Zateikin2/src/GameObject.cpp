#pragma once
#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f& loc)
{
	m_picture.setPosition(loc);
}

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(m_picture);
}

bool GameObject::collidesWith(const GameObject& other) const
{
	return m_picture.getGlobalBounds().intersects(other.m_picture.getGlobalBounds());
}
