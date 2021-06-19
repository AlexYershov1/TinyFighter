#pragma once
#include "macros.h"
#include <vector>
#include <string>

class Arena;

bool outOfBounds(const sf::Vector2f&);
void correctDir(sf::Sprite&, Direction);
//A struct that holds the info of a new stage.
//struct StageInfo
//{
//	StageInfo() {}
//	StageInfo(const StageInfo& other) : characterNames(other.characterNames), arenaType(other.arenaType) {}
//	StageInfo( std::vector<int> names, ArenaType type) : characterNames(names), arenaType(type) {}
//
//	std::vector<int> characterNames;
//	ArenaType arenaType;
//};

//template <class MenuWindow>
//typedef bool (*DrawFuncPtr)(sf::RenderWindow&);
//typedef bool (*handleClickFuncPtr)(const sf::Vector2f& , sf::RenderWindow&, Arena&) ;
//typedef bool (*handleMoveFuncPtr)(const sf::Vector2f&) ;
//
//void activateGenericWindow(sf::RenderWindow& window , Arena& arena, 
//	DrawFuncPtr draw, handleClickFuncPtr handleClick, handleMoveFuncPtr handleMove)
//{
//	//window loop
//	while (window.isOpen())
//	{
//		window.clear(sf::Color::White);
//		draw(window);
//		window.display();
//
//		if (auto event = sf::Event{}; window.waitEvent(event))
//		{
//			sf::Vector2f Location;
//			switch (event.type)
//			{
//			case sf::Event::Closed:
//				window.close();
//				break;
//			case sf::Event::MouseButtonReleased:
//				Location = window.mapPixelToCoords
//				({ event.mouseButton.x, event.mouseButton.y });
//				if (handleClick(Location, window, arena))
//					//stageInfo = handleClick(Location, window);
//					return;
//				break;
//			case sf::Event::MouseMoved:
//				Location = (sf::Vector2f)sf::Mouse::getPosition(window);
//				handleMove(Location);
//				break;
//			}
//		}
//	}
//}