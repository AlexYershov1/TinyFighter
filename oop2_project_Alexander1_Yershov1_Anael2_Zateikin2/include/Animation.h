#pragma once
#include "AnimationData.h"

class Animation
{
public:
	Animation(const AnimeMap&, sf::Sprite& );
	~Animation();
	//static Animation& instance();

	bool update(sf::Time, Action); //returns true if finished animation
	void update(sf::Time, Direction);

	void setAnimationTime(const sf::Time&);

private:
	void update(Action);
	void burnigFreezingCase(Action);
	const AnimeMap& m_animeMap;
	sf::Time m_elapsed = {};
	sf::Time m_animationTime;
	int m_index = 0;
	sf::Sprite& m_sprite;
};
