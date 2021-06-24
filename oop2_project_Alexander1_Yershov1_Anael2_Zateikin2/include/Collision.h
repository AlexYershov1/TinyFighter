#pragma once
#include "GameObject.h"

class Collision
{
public:
	static Collision& instance();
	Collision(const Collision&) = delete;
	Collision& operator=(const Collision&) = delete;
	~Collision() = default;

	void processCollision(GameObject&, GameObject&);

private:
	Collision();

};
