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
   
    static ResourcesManager& instance();

    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;

    const sf::Texture& texture(CharacterType character) const { return m_textures[int(character)]; }
    const sf::Texture* texture(ArenaType, BackroundAssets) const; 
    const sf::Font& font() const { return m_font; }

    const AnimeMap& animationData(CharacterType character) { return m_animationData[int(character)]; }
    const AnimeMap& animationData(AttackType attack) { return m_animationData[int(attack)]; }
    AnimeMap alexData() const;
    AnimeMap banditData() const;
    ~ResourcesManager();

private:
	ResourcesManager();
    std::vector<sf::Texture> m_textures;
    std::vector<std::vector<sf::Texture>> m_BGtextures; //backgroung textures
    std::vector<AnimeMap> m_animationData;
    sf::Font m_font;
};
