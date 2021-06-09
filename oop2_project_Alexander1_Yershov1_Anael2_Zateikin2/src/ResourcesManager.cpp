#include "ResourcesManager.h"


ResourcesManager& ResourcesManager::instance()
{
	static ResourcesManager instance;
	return instance;
}

const sf::Texture* ResourcesManager::texture(ArenaType arenaType, BackroundAssets bgAsset) const
{
    return &m_BGtextures[int(arenaType)][int(bgAsset)]; 
}

AnimeMap ResourcesManager::alexData() const
    {

    const auto size = sf::Vector2i(80, 80);
    const auto initSpace = sf::Vector2i(1, 2);

    auto alex = AnimeMap{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart.x += size.x;
        if (currentStart.x > size.x * 10)
        {
            currentStart.x %= size.x * 10;
            currentStart.y += size.y;
        }
        
        return currentStart;
    };

    alex.m_data[ActionType::Standing].emplace_back(currentStart, size);
    alex.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    alex.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    alex.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 4; repeat++)  alex.m_data[ActionType::Walking].emplace_back(nextStart(), size);
    nextStart();    nextStart();
    for (int repeat = 0; repeat < 8; repeat++)  alex.m_data[ActionType::Punching].emplace_back(nextStart(), size);
    nextStart();    nextStart();
    for (int repeat = 0; repeat < 3; repeat++)  alex.m_data[ActionType::Sprinting].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 24; repeat++) nextStart();
    for (int repeat = 0; repeat < 3; repeat++)  alex.m_data[ActionType::Smacked].emplace_back(nextStart(), size);
    //
    // TO DO - ADD ALL OTHER ACTION TEXTURES
    //


    return alex;
}

AnimeMap ResourcesManager::banditData() const
{
    const auto size = sf::Vector2i(80, 80);
    const auto initSpace = sf::Vector2i(1, 2);

    auto bandit = AnimeMap{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart.x += size.x;
        if (currentStart.x > size.x * 10)
        {
            currentStart.x %= size.x * 10;
            currentStart.y += size.y;
        }
        return currentStart;
    };

    bandit.m_data[ActionType::Standing].emplace_back(currentStart, size);
    bandit.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    bandit.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    bandit.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 4; repeat++)  bandit.m_data[ActionType::Walking].emplace_back(nextStart(), size);
    nextStart();    nextStart();
    for (int repeat = 0; repeat < 6; repeat++)  bandit.m_data[ActionType::Punching].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 30; repeat++) nextStart();
    for (int repeat = 0; repeat < 3; repeat++)  bandit.m_data[ActionType::Smacked].emplace_back(nextStart(), size);

    //
    // TO DO - ADD ALL OTHER ACTION TEXTURES
    //


    return bandit;
}

ResourcesManager::~ResourcesManager()
{
}


ResourcesManager::ResourcesManager()
    :m_animationData(int(CharacterType::Max)), m_textures(int(CharacterType::Max)),
    m_BGtextures(int(ArenaType::Max))
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

    //sf::Texture* background = new sf::Texture{}, * ground = new sf::Texture{};
    //load arena's textures
    if (!image.loadFromFile("bc2.png"))
    {
        throw std::runtime_error("Can't load file");
    }
      
    m_BGtextures[int(ArenaType::Arena1)].push_back(image);
    if (!image.loadFromFile("bc5.png"))
    {
        throw std::runtime_error("Can't load file");
    }
    m_BGtextures[int(ArenaType::Arena1)].push_back(image);
    
}
