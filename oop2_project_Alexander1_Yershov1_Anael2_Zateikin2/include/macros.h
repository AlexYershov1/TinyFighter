#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <unordered_map>


//grapics
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float FULL_WINDOW_W = 1200;

const int CAPTION_HEIGHT = 100;
const int TERRAIN_HIGHT = 200;
const float ICON_SIZE = 512;
const int SEED = 7;
const auto OFFLINE = -1;

// sounds
const auto VOLUME = 10.f;

//menu graphics
const int HEADER_SIZE = 60;
const int REG_CHAR_SIZE = 25;
const float OUTLINE_THICKNESS = 5.0;
const float BOLD_OUTLINE = 10.0;
const sf::Vector2f HEADER_POS = { WINDOW_WIDTH / 2 , 60 };
const sf::Vector2f COMMANDS_POS = { WINDOW_WIDTH / 2 , 110 };
const sf::Vector2f CENTER = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
const sf::Vector2f RECT_SIZE = { 200.f, 200.f };
const sf::Vector2f ARROW_SIZE = { 100.f, 50.f };

const float VERTICAL_OFFSET = 110.f;
const auto BUTTONS_ON_SIDE = 3;
const auto ADJUST = 50.f;

// animation
const auto AnimationTime = sf::seconds(0.1f);
const auto SlowAnimationTime = sf::seconds(0.25f);
const auto SPEED = 100.f;
const auto RUN_SPEED = 180.f;
const auto FADING_TIME = sf::seconds(5.f);


const auto EPSILON = 40.f;
const auto YAxis = 0;
const auto XAxis = 1;
const auto collisionDistance = 60.f;
const auto WaitTime = 0.2;
const auto THUMBNAIL = 1;
const auto OFFSET_SPECIAL_ATTACK_X = 20.f;
const auto OFFSET_SPECIAL_ATTACK_Y = 40.f;

// game statistics
const auto SPECIAL_DELAY = sf::seconds(1.f);
const auto PUNCHING_DELAY = 0.8f;
const auto BURNING_DAMAGE = 10.f;
const auto PUNCH_DAMAGE = 10.f;
const auto SPECIAL_DINAM_DAMAGE = 20.f;
const auto SPECIAL_DINAM_MANA = 30.f;
const auto SPECIAL_STATIC_DAMAGE = 30.f;
const auto SPECIAL_STATIC_MANA = 20.f;
const auto ENEM_DIFFICULTY_CORR = 2;
const auto SIGMA = 30.f;
const auto DEFAULT_KEY = sf::Keyboard::Delete;


// charecters location
const sf::Vector2f INITIAL_LOC = { 100.f ,float(WINDOW_HEIGHT - TERRAIN_HIGHT * 0.90f )};
const auto LOC_OFFSET = 20.f;

//Mana and Helath
const float BAR_WIDTH = 100.f;
const float BAR_HEIGHT = 20.f;
const float MAX_HEALTH = 100.f;
const float MAX_MANA = 100.f;
const float SHADOW_THICKNESS = 1.f;
const float INNER_VERT_SPACE = 20.f;
const float INNER_HORIZ_SPACE = 40.f; //horizontal space

enum class Mode
{
	Server, Client, Offline
};

enum class ActionType
{
	Standing, Walking, Punching, Sprinting, Smacked, hit,
	SpecialStatic, SpecialDynamic, Burning, Freezing, Fading,
};

enum class CharacterType
{
	Alex,
	Anael,
	Bandit,
	//to be continued
	Max
};
enum class PlayerNum
{
	Player1,
	Player2,
	Max
};
enum class AttackType
{
	FireDynamic = int(CharacterType::Max),
	None,
	IceDynamic,
	FireStatic,
	IceStatic,
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
	Arena1, Terrain1, Forest, Terrain2 , Volcano, Terrain3, Max
};
enum class Difficulty
{
	Easy, Normal , Hard, Max
};
enum class BackroundAssets
{
	Background, Ground
};
enum class CharacterAssets
{
	SpriteSheet,
	Thumbnail,
	SmallIcon
};

struct InitialServerInfo
{
	ArenaType m_arena;
	CharacterType m_character;
};

enum class Buttons
{
	Arrows, WASD, I, O, P, C, V, B, Max
};