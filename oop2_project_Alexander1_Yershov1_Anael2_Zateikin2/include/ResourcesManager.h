#pragma once
#include <SFML/graphics.hpp>
#include <vector>
#include "AnimationData.h"
//class AnimationData;

//This is a singleton
class ResourcesManager
{
public:
    enum Objects
    {
        Alex,
        Bandit,
        //to be continued
        Max
    };

    static ResourcesManager& instance();

    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;

    //const sf::Texture& texture() const { return m_texture; }
    //const AnimationData& animationData(Objects object) { return m_data[object]; }
	
	

private:
	ResourcesManager();
    std::vector<sf::Texture> m_textures;
    //std::vector<AnimationData> m_data;


};
