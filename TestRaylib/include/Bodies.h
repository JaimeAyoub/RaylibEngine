#pragma once
#include "include/box2d.h"
#include "raylib.h"
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#include "Entity.h"

class PBox : public Entity {
	b2BodyId body;
	Vector2 size;
	Color color;

public:
	PBox(std::string n, std::string t, b2BodyId id, Vector2 s, bool d):
		Entity(n,t), body(id), size(s)	{
		b2Vec2 b2pos = b2Body_GetPosition(body);
		this->pos = { b2pos.x, b2pos.y };

		b2Rot b2rot = b2Body_GetRotation(body);
		this->angle = b2Rot_GetAngle(b2rot) * RAD2DEG;
		color = d ? RED : GREEN;
	}
	~PBox() { if (b2Body_IsValid(body)) b2DestroyBody(body); }

	void update() override {
		b2Vec2 b2p = b2Body_GetPosition(body);
		pos = { b2p.x,b2p.y };
		angle = b2Rot_GetAngle(b2Body_GetRotation(body)) * RAD2DEG;
	}

	void draw() override {
		Vector2 h = { size.x / 2.0f,size.y / 2.0f };
		b2Vec2 v1 = b2Body_GetWorldPoint(body, { -h.x,-h.y });
		b2Vec2 v2 = b2Body_GetWorldPoint(body, { h.x,-h.y });
		b2Vec2 v3 = b2Body_GetWorldPoint(body, { h.x,h.y });
		b2Vec2 v4 = b2Body_GetWorldPoint(body, { -h.x,h.y });

		DrawRectanglePro({ pos.x,pos.y,size.x,size.y, }, h, angle, Fade(color, 0.8f));

		DrawLineV({ v1.x,v1.y }, { v2.x,v2.y }, color);
		DrawLineV({ v2.x,v2.y }, { v3.x,v3.y }, color);
		DrawLineV({ v4.x,v4.y }, { v4.x,v4.y }, color);
		DrawLineV({ v4.x,v4.y }, { v1.x,v1.y }, color);
	}
};

class PCircle : public Entity {
	b2BodyId body;
	float radius;
	Color color;

public:

	PCircle(std::string n, std::string t, b2BodyId id, float r, bool d)
		:Entity(n, t), body(id), radius(r) {
		b2Vec2 b2pos = b2Body_GetPosition(body);
		this->pos = { b2pos.x, b2pos.y };
		b2Rot b2rot = b2Body_GetRotation(body);
		this->angle = b2Rot_GetAngle(b2rot) * RAD2DEG;

		this->color = d ? SKYBLUE : DARKGRAY;
		color = d ? RED : GREEN;

	}
	~PCircle() { if (b2Body_IsValid(body)) b2DestroyBody(body); }

	void update() override {
		b2Vec2 b2p = b2Body_GetPosition(body);
		pos = { b2p.x,b2p.y };
		angle = b2Rot_GetAngle(b2Body_GetRotation(body)) * RAD2DEG;
	}

	void draw() override {
		DrawCircleLinesV(pos, radius, color);
		DrawCircleV(pos, radius, Fade(color, 0.3f));

		Vector2 dir = { cosf(angle * DEG2RAD), sinf(angle * DEG2RAD) };

		Vector2 scaleDir = Vector2Scale(dir, radius);

		Vector2 endPoint = Vector2Add(pos, scaleDir);

		DrawLineV(pos, endPoint, color);

	}
};
class Bodies
{
};

