#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <unordered_map>


//grapics
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CAPTION_HEIGHT = 100;
const int TERRAIN_HIGHT = 200;
const float ICON_SIZE = 512;
const int SEED = 7;

//menu graphics
const int HEADER_SIZE = 60;
const int REG_CHAR_SIZE = 25;
const float OUTLINE_THICKNESS = 5.0;
const float BOLD_OUTLINE = 10.0;


// animation
const auto AnimationTime = sf::seconds(0.1f);
const auto SPEED = 100.f;

const auto EPSILON = 40.f;
const auto YAxis = 0;
const auto XAxis = 1;
const auto collisionDistance = 60.f;
const auto WaitTime = 0.2;

// game statistics
const int MAX_MANA = 100;
const int MAX_HEALTH = 100;


enum class ActionType
{
	Standing, Walking, Jumping, Punching, Sprinting, Smacked, hit,
	SpecialStatic, SpecialDynamic, Burning, Freezing
};

enum class CharacterType
{
	Alex,
	Anael,
	Bandit,
	//to be continued
	Max
};
enum class AttackType
{
	FireDynamic = int(CharacterType::Max),
	IceDynamic,
	FireStatic,
	IceStatic,
	None,
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

enum class ArenaType
{
	//remove the terrain
	Arena1, Terrain1, Max
};
enum class Difficulty
{
	Easy, Moderate, Hard
};
enum class BackroundAssets
{
	Background, Ground
};