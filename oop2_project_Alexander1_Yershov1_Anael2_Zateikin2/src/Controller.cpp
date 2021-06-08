#pragma once
#include "Controller.h"
#include "MovingObject/Character/Player.h"
#include "Utillities.h"
#include <iostream>

Controller::Controller()
	: m_gameWindow(sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT + CAPTION_HEIGHT), "Game Window",
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
	auto ply = Player{ sf::Vector2f{40.f, 40.f}, CharacterType::Alex };

	// game loop

	while (this->m_gameWindow.isOpen())
	{
		//clear, draw , display
		this->m_gameWindow.clear(sf::Color::White);
		//this->m_gameWindow.draw(ply);
		ply.draw(m_gameWindow);
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

		ply.update(m_elapsed.restart());	// implement in Arena

	}
}
catch (std::exception& ex)
{
	std::cerr << "Fucked: " << ex.what() << '\n';
	return;
}