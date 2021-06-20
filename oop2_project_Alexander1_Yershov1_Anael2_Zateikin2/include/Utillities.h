#pragma once
#include "macros.h"
#include <vector>
#include <string>

class Arena;

bool outOfBounds(const sf::Vector2f&);
void correctDir(sf::Sprite&, Direction);