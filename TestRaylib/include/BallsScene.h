#pragma once
#include "SceneBase.h"
#include "raylib.h"
#include "Ball.h"
#include <vector>

class BallsScene:
	public SceneBase
{
public:
	void Load() override;
	void UnLoad() override;
	void Update() override;
	void Draw() override;
	void PressButton();
	
private:
	std::vector<Ball*> bolitas;
	Rectangle button;
};


