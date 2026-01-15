#include "Ball.h"

Ball::Ball()
{
	posX = GetMouseX();
	posY = GetMouseY();

}

void Ball::UpdateBall()
{
	posY += 9.81;
	posX += velocityX;

	if (posY >= GetScreenHeight() - radius)
	{
		posY = GetScreenHeight() - radius;
	}
	if (posX >= GetScreenWidth() - radius)
	{
		velocityX *= -1;
	}
	if (posX <= radius)
	{
		velocityX *= -1;
	}

}

void Ball::DrawBall()
{
	DrawCircle(posX, posY, radius, color);
}
