#include "Arena.h"


Arena::Arena()
{
	//get the backgroung texture
}

void Arena::createArena()
{
	m_background.setTexture( ResourcesManager::instance().texture(ArenaType::Arena1, BackroundAssets::Background));
	m_background.setSize({ float(WINDOW_WIDTH), float(WINDOW_HEIGHT - TERRAIN_HIGHT- CAPTION_HEIGHT) });
	m_background.setPosition({ 0,0+CAPTION_HEIGHT });
	
	m_ground.setTexture(ResourcesManager::instance().texture(ArenaType::Arena1, BackroundAssets::Ground));

	m_ground.setSize({ float(WINDOW_WIDTH), float(TERRAIN_HIGHT) });
	m_ground.setPosition({ 0,float(WINDOW_HEIGHT - TERRAIN_HIGHT) });
}

void Arena::draw(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_ground);
}

Arena::~Arena()
{
}
