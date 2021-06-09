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
    const std::pair<sf::Texture*, sf::Texture*> texture(ArenaType arenaType) const { return m_BGtextures[int(arenaType)]; }
    const AnimeMap& animationData(CharacterType character) { return m_animationData[int(character)]; }
    AnimeMap alexData() const;
    AnimeMap banditData() const;
    ~ResourcesManager();

private:
	ResourcesManager();
    std::vector<sf::Texture> m_textures;
    std::vector<std::pair<sf::Texture*, sf::Texture*>> m_BGtextures; //backgroung textures
    std::vector<AnimeMap> m_animationData;

    
};