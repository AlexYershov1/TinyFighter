#pragma once
#include "Controller.h"
#include "Character/Player.h"
#include "Character/Enemy.h"
#include "Utillities.h"
#include "RestartExc.h"
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

void Controller::restart()
{
	do
	{
		run();
		m_arena.clear();
		m_view.reset(sf::FloatRect(0, 0, float(WINDOW_WIDTH), float(WINDOW_HEIGHT)));
		m_gameWindow.setView(m_view);
	} while (this->m_gameWindow.isOpen());
}

void Controller::run() try
{
	m_menu.activateMenu(m_gameWindow, m_arena);		//create objects

	// game loop
	while (this->m_gameWindow.isOpen())
	{
		alignView();
		//clear, draw , display
		this->m_gameWindow.clear(sf::Color::White);
		m_states.draw(m_gameWindow);				//draw the life an mana section
		m_arena.draw(m_gameWindow);					//draw all the game objects
		this->m_gameWindow.display();

		for (auto evnt = sf::Event(); m_gameWindow.pollEvent(evnt); )
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				m_gameWindow.close();
				break;
			case sf::Event::MouseButtonReleased:	// stopping and resuming background music
				break;
			default:
				break;
			}
		}
		auto time = m_elapsed.restart();
		m_arena.move(time);
		m_states.move();							//keep the states sction on screen
		
		
		m_arena.collision(m_gameWindow);			//check collisions

		m_arena.update(time);						//update animation
	}
}

catch (RestartExc& ex)
{
	return;
}
catch (std::exception& ex)
{
	std::cerr << "problem: " << ex.what() << '\n';
	return;
}

//This function aligns the view according to player number 1
void Controller::alignView()
{
	auto centerLocation = m_arena.getFirstPlayerPos();
	centerLocation.y = WINDOW_HEIGHT / 2.f;
	
	//if too close to left border
	if(centerLocation.x < WINDOW_WIDTH /2.f)
		m_view.reset(sf::FloatRect(0, 0, float(WINDOW_WIDTH), float(WINDOW_HEIGHT)));

	//if too close to rightBorder
	else if(FULL_WINDOW_W-centerLocation.x < WINDOW_WIDTH/2.f)
		m_view.reset(sf::FloatRect(FULL_WINDOW_W-WINDOW_WIDTH, 0, float(WINDOW_WIDTH), float(WINDOW_HEIGHT)));

	else
		m_view.setCenter(centerLocation);
	
	m_gameWindow.setView(m_view);

	//for captions to stay in the view
	m_states.setRelativeStart({ m_view.getCenter().x - WINDOW_WIDTH / 2.f,0 }); 
}