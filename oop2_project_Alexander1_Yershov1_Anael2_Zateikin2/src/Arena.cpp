#include "Arena.h"
#include "Character/Player.h"
#include "Character/Enemy.h"

Arena::Arena()
{
}

void Arena::createArena()
{
	
	
}

void Arena::createPlayer( CharacterType type )
{
	auto location = INITIAL_LOC;
	location.x += LOC_OFFSET * m_gameObjects.size();
	auto ply = std::make_shared<Player>(location, type, Player::getCount());
	m_gameObjects.push_back(ply);
	m_playerLocations.push_back(ply->getLocation());
}

void Arena::createEnemy(CharacterType type)
{
	auto location = INITIAL_LOC;		////CHANGE TO CORNERS
	location.x = WINDOW_WIDTH - LOC_OFFSET ;
	location.y += LOC_OFFSET * (m_gameObjects.size()-1);
	m_gameObjects.emplace_back(std::make_shared<Enemy>(m_playerLocations, location, type));
}

void Arena::createSpecialAttack(ActionType actionType, AttackType attackType, Character* owner)
{
	actionType == ActionType::SpecialDynamic ?
		m_tempHolder.emplace_back(std::make_shared<DynamicAttack>(owner->getLocation(), attackType, owner)) :
		m_tempHolder.emplace_back(std::make_shared<StaticAttack>(owner->getLocation(), attackType, owner));
}

void Arena::setArenaBackground(ArenaType arenaType)
{
	m_background.setTexture(ResourcesManager::instance().texture(arenaType, BackroundAssets::Background));
	m_background.setSize({ float(WINDOW_WIDTH), float(WINDOW_HEIGHT - TERRAIN_HIGHT - CAPTION_HEIGHT) });
	m_background.setPosition({ 0,0 + CAPTION_HEIGHT });

	m_ground.setTexture(ResourcesManager::instance().texture(arenaType, BackroundAssets::Ground));

	m_ground.setSize({ float(WINDOW_WIDTH), float(TERRAIN_HIGHT) });
	m_ground.setPosition({ 0,float(WINDOW_HEIGHT - TERRAIN_HIGHT) });
}

void Arena::draw(sf::RenderWindow& window) const
{
	window.draw(m_background);
	window.draw(m_ground);
	
	for (const auto& object : m_gameObjects)
		object->draw(window);
}

void Arena::move(const sf::Time& deltaTime)
{
	m_tempHolder.clear();
	for (auto& object : m_gameObjects)
	{
		if(object)
			object->move(deltaTime, *this); //suicides when has three objects in the vector
	}
	//move from tempHolder to main vector
	for (auto& newObj : m_tempHolder)
	{
		m_gameObjects.push_back(std::move(newObj));
	}
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
	//remove all dead objects
	for (auto& object : m_gameObjects)
		object->correctOwnersPtr();

	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); )
	{
		if (!(*it)->isAlive()) //if dead
			it = m_gameObjects.erase(it);
		else
			++it;
	}
}

Arena::~Arena()
{
}
