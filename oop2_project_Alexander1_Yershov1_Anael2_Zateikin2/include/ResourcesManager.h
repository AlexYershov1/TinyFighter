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

    const sf::Texture& texture(int object, int index) const { return m_textures[object][index]; }
    const sf::Texture* texture(ArenaType, BackroundAssets) const; 
    const sf::Texture* menuBGTexture() const { return &m_MenuBackground; }
    const sf::Texture* arrowTexture() const { return &m_arrow; }
    const sf::Font& font() const { return m_font; }

    const AnimeMap& animationData(CharacterType character) { return m_animationData[int(character)]; }
    const AnimeMap& animationData(AttackType attack) { return m_animationData[int(attack)]; }
    
    ~ResourcesManager();

private:
	ResourcesManager();
    std::vector<std::vector<sf::Texture>> m_textures;
    std::vector<std::vector<sf::Texture>> m_BGtextures; //backgroung textures
    std::vector<AnimeMap> m_animationData;
    sf::Texture m_MenuBackground;
    sf::Texture m_arrow;
    sf::Font m_font;

    void loadImage(const std::string&, int);
    void loadArenaImages(const std::string&, const std::string&, int);
    AnimeMap playerData() const;
    AnimeMap banditData() const;
    AnimeMap dynamicData() const;
    AnimeMap staticFireData() const;
    AnimeMap staticIceData() const;
};
