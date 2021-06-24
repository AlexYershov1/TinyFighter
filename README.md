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
The class is also responsile for the view of the window.


Arena:
Holds a vector of of the game objects. Responsible to search for collisions between objects and send to 
the multymethod class "Collision".
There might be two players - playing one vs another.

GameObject: 
An abstract class which represents a game object. Holds a member of strite.

MovingObject:
Derived from GameObject, also an abstract class with a virtual function move.

Character :
Derived from GameObject,  represents a character. A character can have special attacks, which are NonCharacter.
A character can attack and receive damage.

NonCharacter:
A non-living object, such as a fire ball, ice ball, and maybe also throwable objects, such as a rock.
A nonCharacter can move and deal damage.

Player:
Derived from Character. This is a player controlled by the keyboard

Enemy:
Derived from Character. The enemy is controlled by the computer and tries to attack players.

Animation :
a class which deals with a GameObject's sprite sheet and privides the wished animation.

The classes resourceManager and Collisions are singletons. 
resourceManager - for uploading fonts, sounds and textures
Collisions - to hold function table for dealing with collisions.

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

