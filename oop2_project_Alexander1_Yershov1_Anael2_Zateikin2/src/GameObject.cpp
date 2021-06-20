#pragma once
#include "GameObject.h"


GameObject::GameObject(const sf::Vector2f& loc)
	:m_alive(true), m_speed(SPEED)
{
	m_picture.setPosition(loc);
}

void GameObject::draw(sf::RenderWindow& window) const
{
	window.draw(m_picture);
}

bool GameObject::isAlive() const
{
	return m_alive;
}

bool GameObject::collidesWith(const GameObject& other) const
{
	return m_picture.getGlobalBounds().intersects(other.m_picture.getGlobalBounds());
}
