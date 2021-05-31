#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>


//grapics
const int WINDOW_WIDTH = 1500;
const int WINDOW_HEIGHT = 800;
const int CAPTION_HEIGHT = 100;
const float ICON_SIZE = 512;
const int SEED = 7;

enum class Action
{
	Standing, Walking, Jumping, Punching
};

enum class Direction
{
	Start, Right, Down, Left, Up, Stay, End
};
	inline Direction operator++(Direction& x)
	{
		return x = (Direction)(std::underlying_type<Direction>::type(x) + 1);
	}
	inline sf::Vector2f convert(Direction dir)
	{
		switch (dir)
		{
		case Direction::Up:			return { 0, -1 };		case Direction::Down:			return { 0, 1 };		case Direction::Right:			return { 1, 0 };		case Direction::Left:			return { -1, 0 };		case Direction::Stay:			return { 0, 0 };		default:			throw std::runtime_error("Unknown direction");
		}
	}

	inline Direction opposite(Direction dir)	{		switch (dir)		{		case Direction::Up:			return Direction::Down;		case Direction::Down:			return Direction::Up;		case Direction::Right:			return Direction::Left;		case Direction::Left:			return Direction::Right;		case Direction::Stay:			return Direction::Stay;		default:			throw std::runtime_error("Unknown direction");		}	}
