#pragma once
#include "raylib.h"
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
	
};

