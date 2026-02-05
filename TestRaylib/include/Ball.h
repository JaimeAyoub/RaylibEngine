#pragma once
#include "raylib.h"
#include "include/box2d.h"

class Ball
{
public:
	Ball();

	float posX;
	float posY;
	void UpdateBall();
	void DrawBall();


private:
	float velocityX = 2.0f;
	const float radius = 50.0f;
	Color color = RED;
	Texture2D kirby = LoadTexture("assets/textures/kirbyGordo.png");
	
};

