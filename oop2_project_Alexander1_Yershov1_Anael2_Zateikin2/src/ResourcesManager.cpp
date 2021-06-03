#include "ResourcesManager.h"
//#include "AnimationData.h"


inline ResourcesManager& ResourcesManager::instance()
{
	static ResourcesManager instance;
	return instance;
}

//AnimeMap ResourcesManager::alexData() const
//{

namespace
{
    AnimeMap alexData()
    {

    const auto size = sf::Vector2i(40, 40);
    const auto initSpace = sf::Vector2i(1, 2);
    const auto middleSpace = sf::Vector2i(0, 10);

    auto alex = AnimeMap{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart += middleSpace;
        currentStart.x += size.x;
        return currentStart;
    };

    alex.m_data[Action::Standing].emplace_back(currentStart, size);
    alex.m_data[Action::Standing].emplace_back(nextStart(), size);
    alex.m_data[Action::Standing].emplace_back(nextStart(), size);
    alex.m_data[Action::Standing].emplace_back(nextStart(), size);
    alex.m_data[Action::Walking].emplace_back(nextStart(), size);
    alex.m_data[Action::Walking].emplace_back(nextStart(), size);
    alex.m_data[Action::Walking].emplace_back(nextStart(), size);
    alex.m_data[Action::Walking].emplace_back(nextStart(), size);

    //
    // TO DO - ADD ALL OTHER ACTION TEXTURES
    //


    return alex;
}

AnimeMap banditData()
{
    const auto size = sf::Vector2i(40, 40);
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

    bandit.m_data[Action::Standing].emplace_back(currentStart, size);
    bandit.m_data[Action::Standing].emplace_back(nextStart(), size);
    bandit.m_data[Action::Standing].emplace_back(nextStart(), size);
    bandit.m_data[Action::Standing].emplace_back(nextStart(), size);
    bandit.m_data[Action::Walking].emplace_back(nextStart(), size);
    bandit.m_data[Action::Walking].emplace_back(nextStart(), size);
    bandit.m_data[Action::Walking].emplace_back(nextStart(), size);
    bandit.m_data[Action::Walking].emplace_back(nextStart(), size);

    //
    // TO DO - ADD ALL OTHER ACTION TEXTURES
    //


    return bandit;
}
}

ResourcesManager::ResourcesManager()
    :m_animationData(int(CharacterType::Max)), m_textures(int(CharacterType::Max))
{
    //for (auto& texture : m_textures)
    //{
    sf::Texture image;
    if (!image.loadFromFile("davis_0.bmp"))
    {
        throw std::runtime_error("Can't load file");
    }
    m_textures[int(CharacterType::Alex)] = image;
    if (!image.loadFromFile("bandit_0.bmp"))
    {
        throw std::runtime_error("Can't load file");
    }
    //m_textures.push_back(image);
    m_textures[int(CharacterType::Bandit)] = image;



    m_animationData[int(CharacterType::Alex)] = alexData();
    m_animationData[int(CharacterType::Bandit)] = banditData();
}
