#include "ResourcesManager.h"



inline ResourcesManager& ResourcesManager::instance()
{
	static ResourcesManager instance;
	return instance;
}

ResourcesManager::ResourcesManager()
{
    //for (auto& texture : m_textures)
    //{
    sf::Texture image;
    if (!image.loadFromFile("davis_0.bmp"))
    {
        throw std::runtime_error("Can't load file");
    }
    m_textures.push_back(image);
    if (!image.loadFromFile("bandit_0.bmp"))
    {
        throw std::runtime_error("Can't load file");
    }
    m_textures.push_back(image);


    //}
   

    //m_data[Pacman] = pacmanData();
    //m_data[RedGhost] = redGhostData();
}