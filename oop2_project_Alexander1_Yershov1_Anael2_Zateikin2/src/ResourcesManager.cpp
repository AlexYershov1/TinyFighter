#include "ResourcesManager.h"
//#include "AnimationData.h"


ResourcesManager& ResourcesManager::instance()
{
	static ResourcesManager instance;
	return instance;
}

//namespace
//{
AnimeMap ResourcesManager::alexData() const
    {

    const auto size = sf::Vector2i(80, 80);
    const auto initSpace = sf::Vector2i(1, 2);
    const auto middleSpace = sf::Vector2i(0, 0);

    auto alex = AnimeMap{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.x += size.x;
        return currentStart;
    };

    alex.m_data[ActionType::Standing].emplace_back(currentStart, size);
    alex.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    alex.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    alex.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    alex.m_data[ActionType::Walking].emplace_back(nextStart(), size);
    alex.m_data[ActionType::Walking].emplace_back(nextStart(), size);
    alex.m_data[ActionType::Walking].emplace_back(nextStart(), size);
    alex.m_data[ActionType::Walking].emplace_back(nextStart(), size);

    //
    // TO DO - ADD ALL OTHER ACTION TEXTURES
    //


    return alex;
}

AnimeMap ResourcesManager::banditData() const
{
    const auto size = sf::Vector2i(100, 100);
    const auto initSpace = sf::Vector2i(1, 2);
    const auto middleSpace = sf::Vector2i(0, 10);

    auto bandit = AnimeMap{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.x += size.x;
        return currentStart;
    };

    bandit.m_data[ActionType::Standing].emplace_back(currentStart, size);
    bandit.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    bandit.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    bandit.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    bandit.m_data[ActionType::Walking].emplace_back(nextStart(), size);
    bandit.m_data[ActionType::Walking].emplace_back(nextStart(), size);
    bandit.m_data[ActionType::Walking].emplace_back(nextStart(), size);
    bandit.m_data[ActionType::Walking].emplace_back(nextStart(), size);

    //
    // TO DO - ADD ALL OTHER ACTION TEXTURES
    //


    return bandit;
}
//}

ResourcesManager::ResourcesManager()
    :m_animationData(int(CharacterType::Max)), m_textures(int(CharacterType::Max))//,
    //m_BGtextures(int(ArenaType::Max))
{
    //create characters' animations
    sf::Texture image;
    if (!image.loadFromFile("davis_0.png"))
    {
        throw std::runtime_error("Can't load file");
    }
    m_textures[int(CharacterType::Alex)] = image;

    if (!image.loadFromFile("bandit_0.png"))
    {
        throw std::runtime_error("Can't load file");
    }
    m_textures[int(CharacterType::Bandit)] = image;

    m_animationData[int(CharacterType::Alex)] = alexData();
    m_animationData[int(CharacterType::Bandit)] = banditData();


    //load arena's textures
    if (!image.loadFromFile("bc2.png"))
    {
        throw std::runtime_error("Can't load file");
    }
    m_BGtextures.push_back(image);
    if (!image.loadFromFile("bc5.png"))
    {
        throw std::runtime_error("Can't load file");
    }
    m_BGtextures.push_back(image);
    
}
