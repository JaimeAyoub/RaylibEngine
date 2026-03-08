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
	DrawText("Go to Game", button.x + 10, button.y + 20, 14, WHITE);
	DrawText("Bienvenido", GetScreenWidth()/2 - 50, 0, 20, BLACK);

	DrawText("Hola, bienvenido a una especie de Cut the rope.",
		GetScreenWidth() / 2 - 250, 100, 20, BLACK);

	DrawText("Antes de que preciones el boton de arriba para ir al juego, te comento como se juega.",
		GetScreenWidth() / 2 - 380, 150, 18, BLACK);


	DrawText("Veras lineas negras que representan las cuerdas. ",
		GetScreenWidth() / 2 - 250, 200, 20, BLACK);
	DrawText("Manten el click izquierdo para empezar a dibujar una linea. ",
		GetScreenWidth() / 2 - 300, 250, 20, BLACK);
	DrawText("Si tu linea choca contra una cuerda, la cortara. ",
		GetScreenWidth() / 2 - 250, 300, 20, BLACK);

	DrawText("El objetivo es que la bola toque a la plataforma de debajo ",
		GetScreenWidth() / 2 - 300, 350, 20, BLACK);
}

void GameScene::PressButton()
{
	if (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(0))
	{
		buttonPressed = true;
	}


}
