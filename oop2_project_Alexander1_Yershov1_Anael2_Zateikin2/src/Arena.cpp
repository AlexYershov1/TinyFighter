#include "Arena.h"
#include "Character/Player.h"
#include "Character/Enemy.h"

Arena::Arena()
{
	//get the backgroung texture
}
/*
void Arena::createArena()
{
	m_background.setTexture( ResourcesManager::instance().texture(info.arenaType, BackroundAssets::Background));
	m_background.setSize({ float(WINDOW_WIDTH), float(WINDOW_HEIGHT - TERRAIN_HIGHT- CAPTION_HEIGHT) });
	m_background.setPosition({ 0,0+CAPTION_HEIGHT });
	
	m_ground.setTexture(ResourcesManager::instance().texture(info.arenaType, BackroundAssets::Ground));

	m_ground.setSize({ float(WINDOW_WIDTH), float(TERRAIN_HIGHT) });
	m_ground.setPosition({ 0,float(WINDOW_HEIGHT - TERRAIN_HIGHT) });
	
	//create factory
	
}
*/
void Arena::createPlayer( CharacterType type )
{
	auto location = INITIAL_LOC;
	location.x += LOC_OFFSET * m_gameObjects.size();
	auto ply = std::make_shared<Player>(location, type);
	m_gameObjects.push_back(ply);
	m_playerLocations.push_back(ply->getLocation());
}

void Arena::createEnemy(CharacterType type)
{
	auto location = INITIAL_LOC;		////CHANGE TO CORNERS
	location.x += LOC_OFFSET * m_gameObjects.size();
	m_gameObjects.emplace_back(std::make_shared<Enemy>(m_playerLocations, location, type));
}

void Arena::createSpecialAttack(ActionType actionType, AttackType attackType, Character* owner)
{
	actionType == ActionType::SpecialDynamic ?
		m_gameObjects.emplace_back(std::make_shared<DynamicAttack>(owner->getLocation(), attackType, owner)) :
		m_gameObjects.emplace_back(std::make_shared<StaticAttack>(owner->getLocation(), attackType, owner));
}

void Arena::draw(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_ground);
	for (const auto& object : m_gameObjects)
		object->draw(window);
}

void Arena::move(const sf::Time& deltaTime)
{
	for (auto& object : m_gameObjects)
		object->move(deltaTime, *this);
}

void Arena::update(const sf::Time& deltaTime)
{
	for (auto& object : m_gameObjects)
		object->update(deltaTime);
}

void Arena::collision()
{
	for (auto firstIt = m_gameObjects.begin(); firstIt != m_gameObjects.end(); firstIt++)
		for (auto secondIt = firstIt+1; secondIt != m_gameObjects.end(); secondIt++)
		{
			if((*firstIt)->collidesWith(*(*secondIt)))
				Collision::instance().processCollision(**firstIt, **secondIt);
		}
}

Arena::~Arena()
{
}
