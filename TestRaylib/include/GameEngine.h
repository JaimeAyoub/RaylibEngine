#pragma once
#include "raylib.h"
#include "Log.h"
#include "Ball.h"
#include <vector>
class GameEngine {
public:
	GameEngine();
	~GameEngine();
	void Init();
	void Update();
	void Draw();
	void Run();
	void ShutDown();
	std::vector<Ball> bolitas;
private:

	const int screenWidth = 800;
	const int screenHeight = 450;
};
