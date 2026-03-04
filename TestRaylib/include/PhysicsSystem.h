#pragma once

#include "Bodies.h"
#include <memory>
#include "EventManager.h"
#include "EventTypes.h"
#include <string>


struct BodyData {
	Vector2 pos = { 30.0f,30.0f };
	Vector2 size = { 40.0f,40.0f };
	float radius = 20.0f;
	bool isDynamic = true;
	std::string name = "Entity";
	float density = 1.0f;
	float friction = 0.3f;
	float restitution = 0.5f;
	std::string tag = "Entity";
};

struct PivotData {
	std::string name = "Pivote";
	std::string tag = "Pivote";
	Vector2 pos = { 50,100 };
	float radius = 50;
	bool isDynamic = false;
};

struct JointData {
	std::shared_ptr<b2DistanceJointDef> jointDef;
	std::shared_ptr<b2JointId> jointId;
	std::shared_ptr<PCircle> pivot;
};
class PhysicsSystem
{
private: 
	b2WorldId world;
	float accumulator = 0.0f;
	const float timeStep = 1.0f / 60.0f;

	PhysicsSystem(){
		initWorld();
	}
	void initWorld() {
		b2WorldDef worldDef = b2DefaultWorldDef();
		float lenghtUnitsPerMeter = 40.0f;
		b2SetLengthUnitsPerMeter(lenghtUnitsPerMeter);
		worldDef.gravity = { 0.0f,9.8f *lenghtUnitsPerMeter };
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

		processCollisions();
	}

	void processCollisions() {
		b2ContactEvents events = b2World_GetContactEvents(world);

		for (int i = 0; i < events.beginCount; ++i)
		{
			b2ContactBeginTouchEvent* event = events.beginEvents + i;

			b2BodyId bodyA = b2Shape_GetBody(event->shapeIdA);
			b2BodyId bodyB = b2Shape_GetBody(event->shapeIdB);

			Entity* entA = static_cast<Entity*>(b2Body_GetUserData(bodyA));
			Entity* entB = static_cast<Entity*>(b2Body_GetUserData(bodyB));

			if (entA && entB) {
				b2Vec2 vA = b2Body_GetLinearVelocity(bodyA);
				b2Vec2 vB = b2Body_GetLinearVelocity(bodyB);
				float force = b2Length(b2Sub(vA, vB));

				EventManager::instance().emit(CollisionEvent{ entA,entB,force });
			}
		}
	}

	std::shared_ptr<PBox> makeBox(const BodyData& data) {
		return makeBox(data.name, data.tag, data.pos, data.size, data.isDynamic);
	}

	std::shared_ptr<PCircle> makeCircle(const BodyData& data) {
		return makeCircle(data.name, data.tag, data.pos, data.radius, data.isDynamic);
	}

	std::shared_ptr<PBox> makeBox(std::string name, std::string tag, Vector2 pos, Vector2 size, bool isDynamic) {
		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
		bodyDef.position = { pos.x,pos.y };
		bodyDef.linearDamping = 0.0f;
		bodyDef.angularDamping = 0.0f;
		b2BodyId bodyId = b2CreateBody(world, &bodyDef);

		b2ShapeDef shadeDef = b2DefaultShapeDef();
		shadeDef.density = 0.001f;

		shadeDef.enableContactEvents = true;

		b2Polygon box = b2MakeBox(size.x / 2.0f, size.y / 2.0f);
		b2CreatePolygonShape(bodyId, &shadeDef, &box);
		
		auto boxEntity = std::make_shared<PBox>(name, tag, bodyId, size, isDynamic);

		b2Body_SetUserData(bodyId, boxEntity.get());
		
		return boxEntity;
	}

	std::shared_ptr<PCircle> makeCircle(std::string name, std::string tag, Vector2 pos, float radius, bool isDynamic) {
		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
		bodyDef.position = { pos.x,pos.y };
		bodyDef.linearDamping = 0.0f;
		bodyDef.angularDamping = 0.0f;
		b2BodyId bodyId = b2CreateBody(world, &bodyDef);
		b2Body_SetLinearDamping(bodyId, 0.0f);

		b2ShapeDef shadeDef = b2DefaultShapeDef();
		shadeDef.density = 0.01f;

		shadeDef.enableContactEvents = true;
		b2Circle cirlce = { {0.0f,0.0f},radius };
		b2CreateCircleShape(bodyId, &shadeDef, &cirlce);

		auto circleEntity = std::make_shared<PCircle>(name, tag, bodyId, radius, isDynamic);

		b2Body_SetUserData(bodyId, circleEntity.get());

		return circleEntity;
	}
	b2WorldId ReturnWorld()
	{
		return world;
	}

	std::shared_ptr <JointData> makeJoint(std::shared_ptr<PCircle> Pivote, std::shared_ptr<PCircle> bola)
	{
		auto jointDef = std::make_shared<b2DistanceJointDef>(b2DefaultDistanceJointDef());

		jointDef->bodyIdA = Pivote->body;
		jointDef->bodyIdB = bola->body;

		jointDef->localAnchorA = { 0, 0 };
		jointDef->localAnchorB = { 0, 0 };

		jointDef->length = 200.0f;

		jointDef->enableSpring = true;
		jointDef->hertz = 2.0f;
		jointDef->dampingRatio = 0.5f;
		
		auto jointId = std::make_shared<b2JointId>(b2CreateDistanceJoint(world, jointDef.get()));

		auto jointData = std::make_shared<JointData>();
		jointData->jointDef = jointDef;
		jointData->jointId = jointId;
		jointData->pivot = Pivote;

		return jointData;
	}

	void DeleteJoint(std::shared_ptr<b2JointId> jointID)
	{
		b2DestroyJoint(*jointID);
		*jointID = b2_nullJointId;
	}


};

