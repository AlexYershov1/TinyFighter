#include "MovingObject/Character/Player.h"

Player::Player(const sf::Vector2f& location , CharacterType character)
	:m_animation(ResourcesManager::instance().animationData(character), m_picture)
	//Character(location)
{
	m_picture.setTexture(ResourcesManager::instance().texture(character));
}

Player::~Player()
{
}