#pragma once
#include "Controller.h"

Controller::Controller()
	: m_gameWindow(sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT + CAPTION_HEIGHT), "Game Window",
		sf::Style::Titlebar | sf::Style::Close))
{
	srand(SEED);
}

Controller::~Controller()
{
}

void Controller::run()
{

	// game loop

	while (this->m_gameWindow.isOpen())
	{
		//clear, draw , display
		this->m_gameWindow.clear(sf::Color::White);
		this->m_gameWindow.draw(/*Player*/);
		this->m_gameWindow.display();

		for (auto evnt = sf::Event(); m_gameWindow.pollEvent(evnt); )
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				m_gameWindow.close();
				break;
			case sf::Event::KeyPressed:	
				break;
			case sf::Event::MouseButtonReleased:		// stopping and resuming background music
				break;
			default:
				break;
			}
		}

		move(m_elapsed.restart()); //update here
	}
}