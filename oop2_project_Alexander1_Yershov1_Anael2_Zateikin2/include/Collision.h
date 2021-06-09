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

	// Sample struct for exception throwing
	struct UnknownCollision : public std::runtime_error
	{
		UnknownCollision(GameObject& a, GameObject& b)
			: std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + 
				" and " + typeid(b).name())
		{
		}
	};
private:
	Collision();

};
