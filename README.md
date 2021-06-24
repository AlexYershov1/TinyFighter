# TinyFighter
Written by Alexander Yershov and Anael Zateikin.


This is an action game based on little-fighter 2 built using C++ and SFML graphic library.
The game is a fighting game with different modes:
1) Player vs computer - a player controlled by the keyboard fights enemies which are controlled
   by the computer. There are three difficulty levels, each affects the number of enemies.
2) Player vs Player - two players on one keyboard (key map elaboreated at the end of this document).
   In this mode there are no enemies.
3) Player vs Player Online - two players on same ip address, using "player1"'s keys.
   To connect - first player must create a game, second must join. 

When running the game, the user can pick one of the three modes as stated above. After chosing a mode,
the user picks a character and an arena. If in the first mode (vs computer), the user needs to chose a
difficulty and the game begins.
To win, the player must eliminate his enemies, using punches and special attacks. Special attacks const
energy, displayed as mana bar. Mana restores itself.
Receiving hits causes loss of health (displayed as health bar). When health reaches zero - the player dies.


The classes:
Controller:
A class that runs the game loop - creates the game window, draws the objects and calls the functions in 
the correct order.
The class has a member of Arena, which represents the stage (arena), m_statesSection -a member that represents
the upper part of the window, containing life bars and mana (note: enemies dont display their bars).
The class is also responsile for the view of the window. Note - in PlayerVsPlayer on one keyboard, the view follows 
player 1.

Arena:
Holds a vector of of the game objects. Responsible to create players, enemies and spacial attacks.
This class calls to 3 main actions using polymorphism - move, check collisions and update.
Move - moves all objects (players, enemies and spacial attacks). Check Collisions checks if two objects
intersect, if so - calls the singleton "Collisions" to process collisions, using multymethods.
Update - updates the animation of each object.
Arena is also responsible for distinguishing if the game is online or offline and for that holds a static
member, saving the mode (server, client or offline).

GameObject: 
An abstract class which represents a game object. Mainly a member of sprite, a member for action (struct of enum 
and a direction). Has a pure virtual move function.

Character :
Derived from GameObject,  represents a character. A character can have special attacks.
A character can attack and receive damage. Character has a member of Animation, which is responsible for the animation
of the character.
The class implements the move function and update function.
In addition, the class holds timers for actions to help determine the state of the caracter (disabled or not).
A character holds a ManaAndHealth member, which represents the caracters states (with animation).

Player:
Derived from Character. A player receives its movements from a keys map. In an online mode, a player can be a puppet
and receives its movements from a socket.

Enemy:
Derived from Character. An enemy receives a vector of players' locations and chases the closest player. If a special enemy - will
try a special attack, otherwise, try to move closer to player and punch. Randomly chosing on which axis to move. 
Enemy has a difficulty, which determins how often it's "resting".

Special Attack:
An abstract class, derived from GameObject. A Special Attack can move and deal damage. A Special Attack has a pointer
to it's creator.

Static Attack and Dynamic Attack:
Both are derived from Special Attack.Static attack does not move, dynamic attack does and "dies" when hits a character.


Animation :
a class which deals with a GameObject's sprite sheet and provides the wished animation.

The classes resourceManager and Collisions are singletons. 
resourceManager is responsible for uploading fonts, sounds and textures
Collisions - to hold function table for dealing with collisions.
Has one public function which is processing collision between two objects.

GenericMenu:
This class is an abstract class, which has a function "activate window". This funtion runs a window loop, for a generic
menu - has a header, background and three virtual functions - draw, handleClick and handleMove. The function receives
envents and deals whith them using the virtual functions.

Menu:
Derived from GenericMenu, implenemts the three virtual functions. Has a public function for activating the window, which
calls the super class' activate window function.
This class has a vector of commands, implemented by the commands desighn pattern. Each command is a class which has a virtual
function "execute". Possible windows after Menu are Player Vs Player (online/ offline) , Player Vs Computer. The function
receives the window and the arena by reference and calls the corresponding "create" functions (player/ arena/ enemy...).

ChooseCharacter, ChooseArena, ... :
Classes derived from GenericMenu

Keyboard controlls:
Player 1:
up, left, down, right - arrows
punch - I
special dynmic attack - O
special static attack - P
sprint - Shift

Player 2:
up, left, down, right - W A S D
punch - C
special dynmic attack - V
special static attack - B
sprint - Space

