#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <unordered_map>


//grapics
const int WINDOW_WIDTH = 1500;
const int WINDOW_HEIGHT = 800;
const int CAPTION_HEIGHT = 100;
const float ICON_SIZE = 512;
const int SEED = 7;


// animation
const auto AnimationTime = sf::seconds(0.2f);
const auto SPEED = 50.f;

enum class ActionType
{
	Standing, Walking, Jumping, Punching
};

enum class CharacterType
{
	Alex,
	Bandit,
	//to be continued
	Max
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
		static const
			std::unordered_map<Direction, sf::Vector2f>
			dirToVectorMapping =
		{
			{ Direction::Right, { 1, 0 } },
			{ Direction::Left , { -1, 0 } },
			{ Direction::Up   , { 0, -1 } },
			{ Direction::Down , { 0, 1 } },
			{ Direction::Stay , { 0, 0 } }
		};
		return dirToVectorMapping.at(dir);
	}

	inline Direction opposite(Direction dir)
	{
		switch (dir)
		{
		case Direction::Up:
			return Direction::Down;
		case Direction::Down:
			return Direction::Up;
		case Direction::Right:
			return Direction::Left;
		case Direction::Left:
			return Direction::Right;
		case Direction::Stay:
			return Direction::Stay;
		default:
			throw std::runtime_error("Unknown direction");
		}
	}

using Action = std::pair <ActionType, Direction>;