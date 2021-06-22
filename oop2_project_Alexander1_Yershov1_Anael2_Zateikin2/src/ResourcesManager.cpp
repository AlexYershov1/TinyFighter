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

AnimeMap ResourcesManager::playerData() const
{
    const auto size = sf::Vector2i(80, 80);
    const auto initSpace = sf::Vector2i(1, 2);

    auto player = AnimeMap{};
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

    player.m_data[ActionType::Standing].emplace_back(currentStart, size);
    player.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    player.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    player.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 4; repeat++)  player.m_data[ActionType::Walking].emplace_back(nextStart(), size);
    nextStart();    nextStart();
    for (int repeat = 0; repeat < 8; repeat++)  player.m_data[ActionType::Punching].emplace_back(nextStart(), size);
    nextStart();    nextStart();
    for (int repeat = 0; repeat < 3; repeat++)  player.m_data[ActionType::Sprinting].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 4; repeat++) player.m_data[ActionType::Burning].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 2; repeat++) player.m_data[ActionType::Freezing].emplace_back(nextStart(), size);
    nextStart();
    for (int repeat = 0; repeat < 5; repeat++) player.m_data[ActionType::SpecialDynamic].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 5; repeat++) player.m_data[ActionType::SpecialStatic].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 5; repeat++) player.m_data[ActionType::Fading].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 8; repeat++) nextStart();
    for (int repeat = 0; repeat < 3; repeat++)  player.m_data[ActionType::Smacked].emplace_back(nextStart(), size);


    return player;
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
    bandit.m_data[ActionType::Freezing].emplace_back(nextStart(), size);
    bandit.m_data[ActionType::Freezing].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 6; repeat++)  bandit.m_data[ActionType::Punching].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 4; repeat++) bandit.m_data[ActionType::Burning].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 7; repeat++)  bandit.m_data[ActionType::Smacked].emplace_back(nextStart(), size);
    for (int repeat = 0; repeat < 3; repeat++) nextStart();
    for (int repeat = 0; repeat < 5; repeat++)  bandit.m_data[ActionType::Fading].emplace_back(nextStart(), size);
    return bandit;
}

AnimeMap ResourcesManager::dynamicData() const
{
    const auto size = sf::Vector2i(80, 80);
    const auto initSpace = sf::Vector2i(1, 2);

    auto dynamicObj = AnimeMap{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart.x += size.x;
        if (currentStart.x > size.x * 4)
        {
            currentStart.x %= size.x * 4;
            currentStart.y += size.y;
        }

        return currentStart;
    };

    dynamicObj.m_data[ActionType::Standing].emplace_back(currentStart, size);
    dynamicObj.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    dynamicObj.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    dynamicObj.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    dynamicObj.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    dynamicObj.m_data[ActionType::Standing].emplace_back(nextStart(), size);
    nextStart();    nextStart();
    dynamicObj.m_data[ActionType::hit].emplace_back(nextStart(), size);
    dynamicObj.m_data[ActionType::hit].emplace_back(nextStart(), size);
    dynamicObj.m_data[ActionType::hit].emplace_back(nextStart(), size);
    dynamicObj.m_data[ActionType::hit].emplace_back(nextStart(), size);

    return dynamicObj;
}

AnimeMap ResourcesManager::staticFireData() const
{
    const auto size = sf::Vector2i(160, 150);
    const auto initSpace = sf::Vector2i(1, 2);

    auto fireObj = AnimeMap{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart.x += size.x;
        if (currentStart.x > size.x * 5)
        {
            currentStart.x %= size.x * 5;
            currentStart.y += size.y;
        }

        return currentStart;
    };

    fireObj.m_data[ActionType::Standing].emplace_back(currentStart, size);
    fireObj.m_data[ActionType::hit].emplace_back(currentStart, size);
    for (int repeat = 0; repeat < 7; repeat++)  fireObj.m_data[ActionType::hit].emplace_back(nextStart(), size);

    return fireObj;
}

AnimeMap ResourcesManager::staticIceData() const
{
    const auto size = sf::Vector2i(125, 120);
    const auto initSpace = sf::Vector2i(7, 2);

    auto iceObj = AnimeMap{};
    auto currentStart = sf::Vector2i(0, 0);

    auto nextStart = [&]()
    {
        currentStart.x += size.x;
        currentStart.x += initSpace.x;
        if (currentStart.x > size.x * 6)
        {
            currentStart.x %= size.x * 6;
            currentStart.y += size.y;
        }

        return currentStart;
    };

    iceObj.m_data[ActionType::Standing].emplace_back(currentStart, size);
    iceObj.m_data[ActionType::hit].emplace_back(currentStart, size);
    for (int repeat = 0; repeat < 5; repeat++)  iceObj.m_data[ActionType::hit].emplace_back(nextStart(), size);

    return iceObj;
}

ResourcesManager::~ResourcesManager()
{
}


ResourcesManager::ResourcesManager()
    :m_animationData(int(AttackType::Max)), m_textures(int(AttackType::Max)),
    m_BGtextures(int(ArenaType::Max))
{
    //create characters' animations
    loadImage("firen_0.png", int(CharacterType::Alex)); //sprite sheet
    loadImage("firen_f.png", int(CharacterType::Alex)); //thumbnail
    loadImage("firen_s.png", int(CharacterType::Alex)); //small Icon
    
    loadImage("freeze_0.png", int(CharacterType::Anael));
    loadImage("freeze_f.png", int(CharacterType::Anael));
    loadImage("freeze_s.png", int(CharacterType::Anael)); 
    
    loadImage("bandit_0.png", int(CharacterType::Bandit));
    loadImage("firen_ball.png", int(AttackType::FireDynamic));
    loadImage("freeze_ball.png", int(AttackType::IceDynamic));
    loadImage("firen_exp.png", int(AttackType::FireStatic));
    loadImage("freeze_col.png", int(AttackType::IceStatic));


    // cropping the correct animations
    m_animationData[int(CharacterType::Alex)] = playerData();
    m_animationData[int(CharacterType::Anael)] = playerData();
    m_animationData[int(CharacterType::Bandit)] = banditData();
    m_animationData[int(AttackType::FireDynamic)] = dynamicData();
    m_animationData[int(AttackType::IceDynamic)] = dynamicData();
    m_animationData[int(AttackType::FireStatic)] = staticFireData();
    m_animationData[int(AttackType::IceStatic)] = staticIceData();

    // loading audio
    sf::SoundBuffer audio;

    audio.loadFromFile("burning.wav");
    m_audio.emplace((int)ActionType::Burning, audio);

    audio.loadFromFile("freeze-hit.wav");
    m_audio.emplace((int)ActionType::Freezing, audio);

    audio.loadFromFile("punch-hit.wav");
    m_audio.emplace((int)ActionType::Smacked, audio);

    audio.loadFromFile("freeze_dynamic.wav");
    m_audio.emplace((int)AttackType::IceDynamic, audio);

    audio.loadFromFile("firen-dynamic.wav");
    m_audio.emplace((int)AttackType::FireDynamic, audio);

    audio.loadFromFile("firen-static.wav");
    m_audio.emplace((int)AttackType::FireStatic, audio);

    //load Arenas
    loadArenaImages("bc2.png","bc5.png", int(ArenaType::Arena1));
    loadArenaImages("forest1.png","bc5.png", int(ArenaType::Forest));
    loadArenaImages("volcano1.png","bc5.png", int(ArenaType::Volcano));


    //load font
    if (!m_font.loadFromFile("SundayMorning.ttf"))
    {
        throw std::runtime_error("Can't load font");
    }
    //load Menu background
    if (!m_MenuBackground.loadFromFile("night_background.png"))
    {
        throw std::runtime_error("Can't load file");
    }
    //load arrow
    if (!m_arrow.loadFromFile("arrow.png"))
    {
        throw std::runtime_error("Can't load file");
    }
}

void ResourcesManager::loadImage(const std::string& fileName, int character)
{
    sf::Texture image;
    if (!image.loadFromFile(fileName))
    {
        throw std::runtime_error("Can't load file");
    }

    m_textures[character].emplace_back(image);
}

void ResourcesManager::loadArenaImages(const std::string& background, const std::string& ground, int arenaType)
{
    sf::Texture image;
    if (!image.loadFromFile(background))
    {
        throw std::runtime_error("Can't load file");
    }
    m_BGtextures[arenaType].push_back(image);
    if (!image.loadFromFile(ground))
    {
        throw std::runtime_error("Can't load file");
    }
    m_BGtextures[arenaType].push_back(image);
}
