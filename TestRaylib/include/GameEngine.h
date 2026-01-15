#pragma once
#include "raylib.h"
#include "Log.h"
class GameEngine {
public:
	void Init();
	void Update();
	void Draw();
	void Run();
	void ShutDown();
private:
	Log log;
	const int screenWidth = 800;
	const int screenHeight = 450;
};
