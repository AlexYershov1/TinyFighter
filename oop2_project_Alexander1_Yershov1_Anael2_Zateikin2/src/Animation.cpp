#pragma once
#include "Animation.h"
#include"ResourcesManager.h"



Animation::Animation(const AnimeMap& animeMap, sf::Sprite& sprite)
    :m_animeMap(animeMap), m_sprite(sprite)
{
    update(Action { ActionType::Standing, Direction::Right } );
}

Animation::~Animation()
{
}

void Animation::update (sf::Time delta, Action action)
{
    m_elapsed += delta;
    if (m_elapsed >= AnimationTime)
    {
        m_elapsed -= AnimationTime;
        ++m_index;
        m_index %= m_animeMap.m_data.find(action.first) ->second.size();
        update(action);
    }
}

void Animation::update(Action action)
{
    m_sprite.setTextureRect(m_animeMap.m_data.find(action.first)->second[m_index]);
    
    //if received direction left and looking right or received direction right and looking left
    if ((action.second == Direction::Left && m_sprite.getScale().x > 0) ||
        (action.second == Direction::Right && m_sprite.getScale().x < 0))
        m_sprite.scale(-1, 1);
}
