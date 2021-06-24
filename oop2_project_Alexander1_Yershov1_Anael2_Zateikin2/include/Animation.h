#pragma once
#include "AnimationData.h"

class Animation
{
public:
	Animation(const AnimeMap&, sf::Sprite& );
	~Animation();

	bool update(sf::Time, Action); //returns true if finished animation
	void setAnimationTime(const sf::Time&);

private:
	void update(Action);			
	void burningFreezingCase(Action);	//special case for burning and freezing

	const AnimeMap& m_animeMap;
	sf::Time m_elapsed = {};
	sf::Time m_animationTime;
	int m_index = 0;			//index in AnimationData
	sf::Sprite& m_sprite;		//The sprite of the gameObject
};
