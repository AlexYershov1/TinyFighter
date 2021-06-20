#pragma once
#include "Controller.h"
#include "Character/Player.h"
#include "Character/Enemy.h"
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
	m_menu.activateMenu(m_gameWindow, m_arena); //create objects
	m_arena.createArena();

	// game loop

	while (this->m_gameWindow.isOpen())
	{
		//clear, draw , display
		this->m_gameWindow.clear(sf::Color::White);
		m_states.draw(m_gameWindow);
		m_arena.draw(m_gameWindow);
		/*ply.draw(m_gameWindow);
		enemy.draw(m_gameWindow);*/
		this->m_gameWindow.display();

		for (auto evnt = sf::Event(); m_gameWindow.pollEvent(evnt); )
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				m_gameWindow.close();
				break;
			case sf::Event::MouseButtonReleased:		// stopping and resuming background music
				break;
			default:
				break;
			}
		}
		auto time = m_elapsed.restart();
		m_arena.move(time);
		
		//check collisions
		m_arena.collision();
		//Collision::instance().processCollision(ply, enemy);

		m_arena.update(time);
		//ply.update(time);	// implement in Arena
		//enemy.update(time);	// implement in Arena

		
	}
}
catch (std::exception& ex)
{
	std::cerr << "problem: " << ex.what() << '\n';
	return;
}