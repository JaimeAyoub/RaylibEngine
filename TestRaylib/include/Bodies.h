#pragma once
#include "include/box2d.h"
#include "raylib.h"
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#include "Entity.h"
#include "PhysicsEntity.h"

class PBox : public PhysicsEntity {


public:
	Vector2 size;

	PBox(std::string n, std::string t, b2BodyId id, Vector2 s, bool d):
		PhysicsEntity(n,t,id,d),size(s)	{
		
	}


	void draw() override {
		Vector2 h = { size.x / 2.0f,size.y / 2.0f };
		DrawRectanglePro({ pos.x,pos.y,size.x,size.y, }, h, angle, Fade(color, 0.8f));
		b2Vec2 v1 = b2Body_GetWorldPoint(body, { -h.x,-h.y });
		b2Vec2 v2 = b2Body_GetWorldPoint(body, { h.x,-h.y });
		b2Vec2 v3 = b2Body_GetWorldPoint(body, { h.x,h.y });
		b2Vec2 v4 = b2Body_GetWorldPoint(body, { -h.x,h.y });


		DrawLineV({ v1.x,v1.y }, { v2.x,v2.y }, color);
		DrawLineV({ v2.x,v2.y }, { v3.x,v3.y }, color);
		DrawLineV({ v4.x,v4.y }, { v4.x,v4.y }, color);
		DrawLineV({ v4.x,v4.y }, { v1.x,v1.y }, color);
	}
};

class PCircle : public PhysicsEntity {

public:
	float radius;
	PCircle(std::string n, std::string t, b2BodyId id, float r, bool d)
		: PhysicsEntity(n, t, id, d), radius(r) {
	}



	void draw() override {
		DrawCircleLinesV(pos, radius, color);
		DrawCircleV(pos, radius, Fade(color, 0.3f));

		Vector2 dir = { cosf(angle * DEG2RAD), sinf(angle * DEG2RAD) };
		DrawLineV(pos, Vector2Add(pos, Vector2Scale(dir, radius)), color);

	}
};


