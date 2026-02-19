#pragma once
#include <string>
#include "Entity.h"

struct ClickButtonEvent {
	std::string buttonName = "My button";
};

struct CollisionEvent {
	Entity* A;
	Entity* B;
	float force;
};

