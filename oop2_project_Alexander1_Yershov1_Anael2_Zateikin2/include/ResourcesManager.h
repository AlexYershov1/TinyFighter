#pragma once
#include <SFML/graphics.hpp>
#include <vector>
#include "AnimationData.h"
#include "macros.h"
//class AnimationData;

//This is a singleton
class ResourcesManager
{
public:
    /*
    enum Characters
    {
        Alex,
        Bandit,
        //to be continued
        Max
    };
    */

    static ResourcesManager& instance();

    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;

    const sf::Texture& texture(CharacterType character) const { return m_textures[int(character)]; }
   const AnimeMap& animationData(CharacterType character) { return m_animationData[int(character)]; }
    AnimeMap alexData() const;
    AnimeMap banditData() const;
	

private:
	ResourcesManager();
    std::vector<sf::Texture> m_textures;
    std::vector<AnimeMap> m_animationData;

    
};
