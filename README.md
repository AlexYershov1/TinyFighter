# TinyFighter
An action game based on little-fighter 2 built using C++ and SFML graphic library

This is an explenation file for the UML class-diagram.

The classes:
Controller:
A class that runs the game loop - creates the gamw window, draws the objects and receives input.
The class has a member of Arena, which represents the stage (arena)

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
