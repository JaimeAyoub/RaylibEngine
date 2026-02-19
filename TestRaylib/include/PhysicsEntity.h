#pragma once
#include "Entity.h"
#include "include/box2d.h"
class PhysicsEntity : public Entity {
public:
	b2BodyId body;
	Color color;
public:
	PhysicsEntity(std::string n, std::string t, b2BodyId id, bool isDynamic)
		: Entity(n, t), body(id) {
		this->color = isDynamic ? RED : GREEN;
		updatePhysics();

	}
	virtual ~PhysicsEntity() {
		if (b2Body_IsValid(body)) b2DestroyBody(body);
	}
	void update() override {
		updatePhysics();
	}
	void updatePhysics() {
		if (b2Body_IsValid(body)) {
			b2Vec2 b2p = b2Body_GetPosition(body);
			this->pos = { b2p.x,b2p.y };

			b2Rot b2r = b2Body_GetRotation(body);
			this->angle = b2Rot_GetAngle(b2r) * RAD2DEG;
		}
	}
	void setType(b2BodyType type) {
		if (b2Body_IsValid(body)) {
			b2Body_SetType(body, type);
			setAwake(true);
			b2Body_ApplyMassFromShapes(body);
			debugStatus();
		}
	}

	void debugStatus() {
		if (!b2Body_IsValid(body)) {
			printf("Error : Body no valido ! \n");
			return;
		}

		b2Vec2 p = b2Body_GetPosition(body);
		b2BodyType t = b2Body_GetType(body);
		bool awake = b2Body_IsAwake(body);
		float mass = b2Body_GetMass(body);

		printf("Pos : %.2f, %.2f | Tipo: %d | Awake: %d | Masa: %.f \n",
			p.x, p.y, (int)t, (int)awake, mass);
	}

	void setBodyPosition(Vector2 newPos) {
		if (!b2Body_IsValid(body)) return;

		b2Body_SetTransform(body, {newPos.x, newPos.y }, b2Rot_identity);

		b2Body_SetAwake(body, true);

		this->pos = newPos;
	}

	void applyImpulse(Vector2 impulse) {
		if (b2Body_IsValid(body)) {
			b2Body_ApplyLinearImpulseToCenter(body, { impulse.x, impulse.y }, true);
		}
	}

	void setAwake(bool awake) {
		if (b2Body_IsValid(body)) {
			b2Body_SetAwake(body, awake);
		}
	}


};


