#pragma once
#include "Controller.h"
#include "MovingObject/Character/Player.h"
#include "MovingObject/Character/Enemy.h"
#include "Utillities.h"
#include <iostream>

Controller::Controller()
	: m_gameWindow(sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game Window",
		sf::Style::Titlebar | sf::Style::Close))
{
	srand(SEED);
}

Controller::~Controller()
{
}

void Controller::run() try
{
	//create objects
	auto ply = Player{ sf::Vector2f{40.f, 500.f}, CharacterType::Alex };
	auto vecLoc = std::vector<const sf::Vector2f*>{ ply.getLocation() };
	auto enemy = Enemy{ vecLoc, sf::Vector2f{150.f, 500.f}, CharacterType::Bandit };
	m_arena.createArena();
	// game loop

	while (this->m_gameWindow.isOpen())
	{
		//clear, draw , display
		this->m_gameWindow.clear(sf::Color::White);
		//this->m_gameWindow.draw(ply);
		m_arena.draw(m_gameWindow);
		ply.draw(m_gameWindow);
		enemy.draw(m_gameWindow);
		this->m_gameWindow.display();

		for (auto evnt = sf::Event(); m_gameWindow.pollEvent(evnt); )
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				m_gameWindow.close();
				break;
			//case sf::Event::KeyPressed:
				//ply.setAction(toAction(evnt.key.code));
				// update(m_elapsed.restart()); //update here- handle player change
				//break;
			case sf::Event::MouseButtonReleased:		// stopping and resuming background music
				break;
			default:
				break;
			}
		}
		auto time = m_elapsed.restart();
		ply.update(time);	// implement in Arena
		enemy.update(time);	// implement in Arena

	}
}
catch (std::exception& ex)
{
	std::cerr << "Fucked: " << ex.what() << '\n';
	return;
}