#pragma once
#include <SFML/graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "AnimationData.h"
#include "macros.h"

//This is a singleton
class ResourcesManager
{
public:
   
    static ResourcesManager& instance();

    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;

    const sf::Texture& texture(int object, int index) const { return m_textures[object][index]; }
    const sf::Texture* texture(ArenaType, BackroundAssets) const; 
    const sf::Texture* texture(Buttons) const;
    const sf::Texture* menuBGTexture() const { return &m_MenuBackground; }
    const sf::Texture* arrowTexture() const { return &m_arrow; }
    const sf::Font& font() const { return m_font; }
    const sf::SoundBuffer& getSound(int choice) const { return m_audio.at(choice); }

    const AnimeMap& animationData(CharacterType character) { return m_animationData[int(character)]; }
    const AnimeMap& animationData(AttackType attack) { return m_animationData[int(attack)]; }
    
    ~ResourcesManager();

private:
	ResourcesManager();
    std::vector<std::vector<sf::Texture>> m_textures;
    std::vector<sf::Texture> m_buttons;
    std::vector<std::vector<sf::Texture>> m_BGtextures; //backgroung textures
    std::unordered_map<int, sf::SoundBuffer> m_audio;
    std::vector<AnimeMap> m_animationData;
    sf::Texture m_MenuBackground;
    sf::Texture m_arrow;
    sf::Font m_font;

    void loadImage(const std::string&, int);
    void loadImage(const std::string&);
    void loadArenaImages(const std::string&, const std::string&, int);
    AnimeMap playerData() const;
    AnimeMap banditData() const;
    AnimeMap dynamicData() const;
    AnimeMap staticFireData() const;
    AnimeMap staticIceData() const;
};
