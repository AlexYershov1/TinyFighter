#pragma once
#include "Animation.h"
#include"ResourcesManager.h"
#include "Utillities.h"



Animation::Animation(const AnimeMap& animeMap, sf::Sprite& sprite)
    :m_animeMap(animeMap), m_sprite(sprite), m_animationTime(AnimationTime)
{
    update(Action { ActionType::Standing, Direction::Right } );
}

Animation::~Animation()
{
}

// update for character
bool Animation::update (sf::Time delta, Action action)
{
    m_elapsed += delta;
    
    if (m_elapsed >= m_animationTime)
    {
        m_elapsed -= m_animationTime;
        ++m_index;

        // case special attack completed a hit
        if (action.first == ActionType::hit && m_index == m_animeMap.m_data.find(action.first)->second.size())
            return true;
        burningFreezingCase(action);

        m_index %= m_animeMap.m_data.find(action.first) ->second.size();
        update(action);
    }
    return false;
}

void Animation::update(Action action)
{
    m_sprite.setTextureRect(m_animeMap.m_data.find(action.first)->second[m_index]);
    
    correctDir(m_sprite, action.second);
}

void Animation::burningFreezingCase(Action action)
{
    // case character is burning or freezing
    if ((action.first == ActionType::Freezing || action.first == ActionType::Burning)
        && m_index == m_animeMap.m_data.find(action.first)->second.size() - 1)
    {
        update(action);
        m_index--;
    }
}

void Animation::setAnimationTime(const sf::Time& animationTime)
{
    m_animationTime = animationTime;
}
