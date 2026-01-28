#include "GameEngine.h"
#include "raylib.h"
#include "Log.h"
#include "SceneManager.h"
#include "GameScene.h"

GameEngine::GameEngine()
{
	gameScene = new GameScene;
	ballScene = new BallsScene;
	SceneManager::instance().ChangeScene(ballScene);
	
}

GameEngine::~GameEngine()
{
}

void GameEngine::Init()
{

	InitWindow(screenWidth, screenHeight, "GameEngine");
	SetTargetFPS(60);
	Log::print("Ventana inicialziada");
}

void GameEngine::Update()
{
	SceneManager::instance().UpdateScene();
	if (SceneManager::instance().GetCurrentScene()->buttonPressed)
	{
		if (SceneManager::instance().GetCurrentScene() == gameScene)
		{
			SceneManager::instance().ChangeScene(ballScene);

		}
		else
			{
			SceneManager::instance().ChangeScene(gameScene);
		}
	}
	
}

void GameEngine::Draw()
{

	BeginDrawing();

	ClearBackground(RAYWHITE);

	SceneManager::instance().DrawScene();

	EndDrawing();


}

void GameEngine::Run()
{
	while (!WindowShouldClose())
	{
		Update();

		Draw();
	}

}

void GameEngine::ShutDown()
{
	CloseWindow();
}
