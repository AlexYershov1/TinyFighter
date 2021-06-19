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
    auto x = 0;
    if (m_elapsed >= m_animationTime)
    {
        m_elapsed -= m_animationTime;
        ++m_index;

        //export to a new update with new parameters (different animationtime)
        if (action.first == ActionType::hit && m_index == m_animeMap.m_data.find(action.first)->second.size())
            return true;
            
        m_index %= m_animeMap.m_data.find(action.first) ->second.size();
        update(action);
    }
    return false;
}

void Animation::update(Action action)
{
    m_sprite.setTextureRect(m_animeMap.m_data.find(action.first)->second[m_index]);
    
    correctDir(m_sprite, action.second);
    //if ((action.second == Direction::Left && m_sprite.getScale().x > 0) ||
    //    (action.second == Direction::Right && m_sprite.getScale().x < 0))
    //    m_sprite.scale(-1, 1);
}

// update animation for special dynamic attack
void Animation::update(sf::Time delta, Direction dir)
{
    m_elapsed += delta;
    if (m_elapsed >= m_animationTime)
    {
        m_elapsed -= m_animationTime;
        ++m_index;
        m_index %= m_animeMap.m_data.find(ActionType::Standing)->second.size();
        m_sprite.setTextureRect(m_animeMap.m_data.find(ActionType::Standing)->second[m_index]);

        correctDir(m_sprite, dir);
    }
}

void Animation::setAnimationTime(const sf::Time& animationTime)
{
    m_animationTime = animationTime;
}
