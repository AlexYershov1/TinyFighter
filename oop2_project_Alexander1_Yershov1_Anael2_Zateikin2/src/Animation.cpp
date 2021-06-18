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

// update for character
bool Animation::update (sf::Time delta, Action action)
{
    m_elapsed += delta;
    if (m_elapsed >= AnimationTime)
    {
        m_elapsed -= AnimationTime;
        ++m_index;
        if (action.first == ActionType::hit && m_index == m_animeMap.m_data.find(action.first)->second.size())
        {
            //m_alive = false;
            return true;
        }
            
        m_index %= m_animeMap.m_data.find(action.first) ->second.size();
        update(action);
    }
    return false;
}

void Animation::update(Action action)
{
    m_sprite.setTextureRect(m_animeMap.m_data.find(action.first)->second[m_index]);
    
    //if received direction left and looking right or received direction right and looking left
    if ((action.second == Direction::Left && m_sprite.getScale().x > 0) ||
        (action.second == Direction::Right && m_sprite.getScale().x < 0))
        m_sprite.scale(-1, 1);
}

// update animation for special dynamic attack
void Animation::update(sf::Time delta, Direction dir)
{
    m_elapsed += delta;
    if (m_elapsed >= AnimationTime)
    {
        m_elapsed -= AnimationTime;
        ++m_index;
        m_index %= m_animeMap.m_data.find(ActionType::Standing)->second.size();
        m_sprite.setTextureRect(m_animeMap.m_data.find(ActionType::Standing)->second[m_index]);

        //if received direction left and looking right or received direction right and looking left
        if ((dir == Direction::Left && m_sprite.getScale().x > 0) ||
            (dir == Direction::Right && m_sprite.getScale().x < 0))
            m_sprite.scale(-1, 1);
    }
}