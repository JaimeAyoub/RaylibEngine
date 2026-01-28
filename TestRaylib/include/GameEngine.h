#pragma once
#include "GameScene.h"
#include "BallsScene.h"
class GameEngine {
public:
	GameEngine();
	~GameEngine();
	void Init();
	void Update();
	void Draw();
	void Run();
	void ShutDown();

private:

	const int screenWidth = 800;
	const int screenHeight = 450;

	GameScene* gameScene;
	BallsScene* ballScene;

};
