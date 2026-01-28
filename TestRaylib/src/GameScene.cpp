#include "GameScene.h"

void GameScene::Load()
{
	button = { 350,20,100,50 };
	buttonPressed = false;
	Name = "MainMenu Scene";
}

void GameScene::UnLoad()
{

}

void GameScene::Update()
{
	PressButton();
	//Log::print("Update del main menu");
	//Log::print(buttonPressed ? "true" : "false");
}

void GameScene::Draw()
{
	DrawRectangleRec(button, buttonPressed ? RED : DARKGRAY);
	DrawText("Go to Balls", button.x + 10, button.y + 20, 10, WHITE);
	DrawText("Main Menu", GetScreenWidth()/2 - 50, 0, 20, BLACK);
}

void GameScene::PressButton()
{
	if (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(0))
	{
		buttonPressed = true;
	}


}
