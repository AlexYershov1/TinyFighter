#include "Menu/ChooseArena.h"
#include "Arena.h"
#include <cmath>


ChooseArena::ChooseArena()
	:GenericMenu()
{
	auto texturePtr = ResourcesManager::instance().arrowTexture();
	sf::RectangleShape arrowRight, arrowLeft;
	arrowRight.setTexture(texturePtr);
	arrowRight.setSize(ARROW_SIZE);
	sf::FloatRect rect = arrowRight.getLocalBounds();
	arrowRight.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	arrowRight.setPosition({ CENTER.x + RECT_SIZE.x + 50.f, CENTER.y });
	arrowLeft.setTexture(texturePtr);
	arrowLeft.setSize(ARROW_SIZE);
	arrowLeft.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	arrowLeft.setPosition({ CENTER.x - RECT_SIZE.x - 50.f, CENTER.y });
	arrowLeft.scale({ -1,1 });
	m_arrows = { arrowLeft, arrowRight };
	
	//header
	m_header.setCharacterSize(HEADER_SIZE);
	m_header.setString("Choose Arena");
	rect = m_header.getLocalBounds();
	m_header.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	m_header.setPosition(HEADER_POS);
	
	//add arena thumbnails
	sf::RectangleShape thumbnail;
	thumbnail.setTexture(ResourcesManager::instance().texture(ArenaType::Arena1, BackroundAssets::Background));
	m_arenasThumbnails.push_back({ thumbnail, ArenaType::Arena1 });
	thumbnail.setTexture(ResourcesManager::instance().texture(ArenaType::Forest, BackroundAssets::Background));
	m_arenasThumbnails.push_back({ thumbnail, ArenaType::Forest });
	thumbnail.setTexture(ResourcesManager::instance().texture(ArenaType::Volcano, BackroundAssets::Background));
	m_arenasThumbnails.push_back({ thumbnail, ArenaType::Volcano });

	modifyThumbnails();
}

ChooseArena::~ChooseArena()
{
}

ArenaType ChooseArena::getChoice() const
{
	return m_choice;
}

void ChooseArena::activateChooseArena(sf::RenderWindow& window, Arena& arena)
{
	activateWindow(window, arena);
}

void ChooseArena::draw(sf::RenderWindow& window) const
{
	window.draw(m_background);
	window.draw(m_header);
	window.draw(m_arrows.first);
	window.draw(m_arrows.second);
	for (const auto& thumnbail : m_arenasThumbnails)
		window.draw(thumnbail.first);
}

bool ChooseArena::handleClick(const sf::Vector2f& location, sf::RenderWindow& window, Arena& arena)
{
	for (auto& thumbnail : m_arenasThumbnails)
	{
		if (thumbnail.first.getGlobalBounds().contains(location))
		{
			m_choice = thumbnail.second;
			arena.setArenaBackground(thumbnail.second); //set the arena's background type
			return true;
		}
	}
	if (m_arrows.first.getGlobalBounds().contains(location)) //pressed left arrow
	{
		for (auto& thumbnail : m_arenasThumbnails)
		{
			thumbnail.first.move({ - WINDOW_WIDTH, 0 }); //move everyone left
			if (std::abs(thumbnail.first.getPosition().x) >= (m_arenasThumbnails.size()-1) * WINDOW_WIDTH)
				thumbnail.first.setPosition(CENTER);
		}
		return false;
	}
	if (m_arrows.second.getGlobalBounds().contains(location)) //pressed left arrow
	{
		for (auto& thumbnail : m_arenasThumbnails)
		{
			thumbnail.first.move({ WINDOW_WIDTH, 0 }); //move everyone right
			if (std::abs(thumbnail.first.getPosition().x) >= (m_arenasThumbnails.size()) * WINDOW_WIDTH)
				thumbnail.first.setPosition(CENTER);
		}
		return false;
	}

	return false;
}

void ChooseArena::handleMove(const sf::Vector2f& location)
{
	// mark/unmark buttons
	for (auto& thumbnail : m_arenasThumbnails)
	{
		(thumbnail.first.getGlobalBounds().contains(location)) ? mark(thumbnail.first) : unmark(thumbnail.first);
	}
	(m_arrows.first.getGlobalBounds().contains(location)) ? mark(m_arrows.first) : unmark(m_arrows.first);
	(m_arrows.second.getGlobalBounds().contains(location)) ? mark(m_arrows.second) : unmark(m_arrows.second);
}

void ChooseArena::modifyThumbnails()
{
	int offsetCoeff = 0;
	for (auto& thumbnail : m_arenasThumbnails)
	{
		thumbnail.first.setSize(RECT_SIZE);
		sf::FloatRect rect = thumbnail.first.getLocalBounds();
		thumbnail.first.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
		thumbnail.first.setPosition({ CENTER.x + offsetCoeff * WINDOW_WIDTH, CENTER.y }); //show only one on screen
		offsetCoeff++;
	}
}

void ChooseArena::mark(sf::RectangleShape& rect)
{
	rect.setOutlineColor(sf::Color::Yellow);
	rect.setOutlineThickness(BOLD_OUTLINE);
}

void ChooseArena::unmark(sf::RectangleShape& rect)
{
	rect.setOutlineColor(sf::Color::Transparent);
	rect.setOutlineThickness(BOLD_OUTLINE);
}
