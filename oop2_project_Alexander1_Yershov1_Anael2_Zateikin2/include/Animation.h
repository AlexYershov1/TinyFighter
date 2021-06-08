#pragma once
//#include "Animation.h"
#include "AnimationData.h"

class Animation
{
public:
	Animation(const AnimeMap&, sf::Sprite& );
	~Animation();
	//static Animation& instance();

	void update(sf::Time delta, Action);

private:
	void update(Action);

	const AnimeMap& m_animeMap;
	sf::Time m_elapsed = {};
	int m_index = 0;
	sf::Sprite& m_sprite;
	//std::unordered_map<Characters, AnimeMap> m_animeMap;
};
