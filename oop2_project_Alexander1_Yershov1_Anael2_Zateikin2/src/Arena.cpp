#include "Arena.h"
#include "Character/Player.h"
#include "Character/Enemy.h"
#include <algorithm>

void* Arena::m_socket;

Arena::Arena() 
	: m_mode(Mode::Offline)
{
}

void Arena::clear()
{
	for (auto& obj : m_gameObjects)
	{
		if (auto ply = dynamic_cast<Player*>(obj.get()))
			ply->resetCount();
	}
	//add setview
	m_gameObjects.clear();
	m_mode = Mode::Offline;
	m_playerLocations.clear();
}

void Arena::createPlayer(CharacterType type, bool isPuppet = false)
{
	auto location = INITIAL_LOC;
	location.x += LOC_OFFSET * m_gameObjects.size();
	auto ply = std::make_unique<Player>(location, type, isPuppet);
	m_playerLocations.push_back(ply->getLocation());
	m_gameObjects.push_back(std::move(ply));
}

void Arena::createEnemy(CharacterType type)
{
	float xLoc = rand() % (int(FULL_WINDOW_W));
	float yLoc = WINDOW_HEIGHT - EPSILON - rand() % (TERRAIN_HIGHT - int(EPSILON));

	m_gameObjects.emplace_back(std::make_unique<Enemy>(m_playerLocations, sf::Vector2f{xLoc, yLoc}, type));
}

void Arena::createSpecialAttack(ActionType actionType, AttackType attackType, Character* owner)
{
	static Effect effect;
	if (attackType != AttackType::IceStatic)
	{
		effect.setSound(attackType);
		effect.play();
	}

	actionType == ActionType::SpecialDynamic ?
		m_tempHolder.emplace_back(std::make_unique<DynamicAttack>(owner->getLocation(), attackType, owner)) :
		m_tempHolder.emplace_back(std::make_unique<StaticAttack>(owner->getLocation(), attackType, owner));
}

void Arena::setMode(Mode mode = Mode::Offline)
{
	m_mode = mode;
}

Mode Arena::getMode() const
{
	return m_mode;
}

void Arena::setArenaBackground(ArenaType arenaType)
{
	m_background.setTexture(ResourcesManager::instance().texture(arenaType, BackroundAssets::Background));
	m_background.setSize({ float(FULL_WINDOW_W), float(WINDOW_HEIGHT - TERRAIN_HIGHT - CAPTION_HEIGHT) });
	m_background.setPosition({ 0,0 + CAPTION_HEIGHT });

	m_ground.setTexture(ResourcesManager::instance().texture(arenaType, BackroundAssets::Ground));

	m_ground.setSize({ float(FULL_WINDOW_W), float(TERRAIN_HIGHT) });
	m_ground.setPosition({ 0,float(WINDOW_HEIGHT - TERRAIN_HIGHT) });
}

void Arena::draw(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_ground);
	
	std::sort(m_gameObjects.begin(), m_gameObjects.end(), 
				[](const std::unique_ptr<GameObject>& first, const std::unique_ptr<GameObject>& second) { return first->y() < second->y(); });

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
	{
		object->update(deltaTime);

		// sending the puppets' 
		/*if (m_mode != Mode::None && dynamic_cast<Player*>(object.get()))
			object->sendAction();*/
	}
	
}

void Arena::collision(sf::RenderWindow& window)
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
		if (!(*it)->isAlive() && (*it)->isFaded()) //if dead
		{
			if (auto ply = dynamic_cast<Player*>(it->get()))
				activateConclusionWindow(false, window, ply->getPlayerNum());

			it = m_gameObjects.erase(it);
		}
		else
			++it;
	}
	if (isWon())
		activateConclusionWindow(true, window);
}

sf::Vector2f Arena::getFirstPlayerPos() const
{
	if (m_gameObjects.empty())
		throw std::runtime_error("no gameObjects");
	
	
	return **(m_playerLocations.begin());
}

void Arena::createSocket()
{
	init_socket_library();
	if (m_mode == Mode::Server) 
		m_socket = server_wait_for_client();
	if (m_mode == Mode::Client)
		m_socket = client_connect_to_server();
}

Arena::~Arena()
{
}

void Arena::activateConclusionWindow(bool isWon, sf::RenderWindow& window, int plyNum)
{
	ConclusionWindow con{ isWon };
	auto view = sf::View(sf::FloatRect(sf::FloatRect(0, 0, float(WINDOW_WIDTH), float(WINDOW_HEIGHT))));
	window.setView(view);
	con.activateConclusionWindow(window, *this, plyNum);
}

bool Arena::isWon() const
{
	return !std::count_if(m_gameObjects.begin(), m_gameObjects.end(),
		[](const std::unique_ptr<GameObject>& obj) { return dynamic_cast<Enemy*>(obj.get()); })
		&& std::count_if(m_gameObjects.begin(), m_gameObjects.end(),
			[](const std::unique_ptr<GameObject>& obj) { return dynamic_cast<Player*>(obj.get()); }) == 1;
}
