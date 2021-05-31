#pragma once
#include "Animation.h"
#include "AnimationData.h"

class Animation
{
public:
	~Animation();
	static Animation& instance();
private:
	Animation();
	Animation(const Animation&) = default;
	Animation& operator=(const Animation&) = default;

	std::unordered_map<std::type_info, AnimeMap> m_anime;
};
