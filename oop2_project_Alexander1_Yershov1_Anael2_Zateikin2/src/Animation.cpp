#pragma once
#include "Animation.h"
#include"ResourcesManager.h"



Animation::Animation(const AnimeMap& animeMap, sf::Sprite& sprite)
    :m_animeMap(animeMap), m_sprite(sprite)
{
    //m_sprite.setTexture(ResourcesManager::instance().texture());
    update(Action::Standing);
}

Animation::~Animation()
{
}

void Animation::update (sf::Time delta, Action actionType)
{
    m_elapsed += delta;
    if (m_elapsed >= AnimationTime)
    {
        m_elapsed -= AnimationTime;
        ++m_index;
        m_index %= m_animeMap.m_data.find(actionType) ->second.size();
        update(actionType);
    }
}

void Animation::update(Action actionType)
{
    m_sprite.setTextureRect(m_animeMap.m_data.find(actionType)->second[m_index]);
}
