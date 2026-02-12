#pragma once

#include "Bodies.h"
#include <memory>
class PhysicsSystem
{
private: 
	b2WorldId world;

	PhysicsSystem(){
		initWorld();
	}
	void initWorld() {
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = { 0.0f,980.0f };
		world = b2CreateWorld(&worldDef);
	}

public:
	~PhysicsSystem() {
		if (b2World_IsValid(world)) {
			b2DestroyWorld(world);
		}
	}

	static PhysicsSystem& instance() {
		static PhysicsSystem ps;
		return ps;
	}

	void reset() {
		if (b2World_IsValid(world)) {
			b2DestroyWorld(world);
		}
		initWorld();
	}

	void update(float dt) {
		b2World_Step(world, dt, 4);
	}

	std::shared_ptr<PBox> makeBox(std::string name, std::string tag, Vector2 pos, Vector2 size, bool isDynamic) {
		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
		bodyDef.position = { pos.x,pos.y };
		b2BodyId bodyId = b2CreateBody(world, &bodyDef);

		b2ShapeDef shadeDef = b2DefaultShapeDef();
		b2Polygon box = b2MakeBox(size.x / 2.0f, size.y / 2.0f);
		b2CreatePolygonShape(bodyId, &shadeDef, &box);
		
		return std::make_shared<PBox>(name, tag, bodyId, size, isDynamic);
	}

	std::shared_ptr<PCircle> makeCircle(std::string name, std::string tag, Vector2 pos, float radius, bool isDynamic) {
		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
		bodyDef.position = { pos.x,pos.y };
		b2BodyId bodyId = b2CreateBody(world, &bodyDef);

		b2ShapeDef shadeDef = b2DefaultShapeDef();
		b2Circle cirlce = { {0.0f,0.0f},radius };
		b2CreateCircleShape(bodyId, &shadeDef, &cirlce);

		return std::make_shared<PCircle>(name, tag, bodyId, radius, isDynamic);
	}
};

