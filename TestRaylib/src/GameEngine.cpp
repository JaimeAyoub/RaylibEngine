#include "GameEngine.h"
#include "raylib.h"
#include "Log.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "include/base.h"

GameEngine::GameEngine()
{
	gameScene = new GameScene;
	ballScene = new BallsScene;
	
}

GameEngine::~GameEngine()
{
}

void GameEngine::Init()
{

	InitWindow(screenWidth, screenHeight, "GameEngine");
	InitAudioDevice();
	SetTargetFPS(60);
	SceneManager::instance().ChangeScene(ballScene);
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
