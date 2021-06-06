#include "MovingObject/Character/Enemy.h"

Enemy::Enemy(/*vector of players' loctions,*/const sf::Vector2f& location, CharacterType character)
	:m_animation(ResourcesManager::instance().animationData(character), m_picture)
{
	m_picture.setTexture(ResourcesManager::instance().texture(character));
}