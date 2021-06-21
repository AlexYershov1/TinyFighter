#pragma once
#include "macros.h"
#include "ResourcesManager.h"
#include <vector>
#include <string>

class Character;
class Arena;

// struct to substitute sf::Sound in order to simplify the code and set buffer a single time
struct Effect
{
	Effect() {}
	Effect(int type)
	{
		m_data.setBuffer(ResourcesManager::instance().getSound(type));
		m_data.setVolume(VOLUME);
	}
	sf::Sound m_data;

	void setSound(AttackType type)
	{
		m_data.setBuffer(ResourcesManager::instance().getSound((int)type));
	}

	void play() { m_data.play(); }
	sf::SoundSource::Status getStatus() { return m_data.getStatus(); }
};

bool outOfBounds(const sf::Vector2f&);
void correctDir(sf::Sprite&, Direction);
void twoCharactersCollision(Character&, Character&);