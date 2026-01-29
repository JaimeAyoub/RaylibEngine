#pragma once
#include "raylib.h"
#include "SceneBase.h"
#include "Ball.h"
#include <vector>
#include <EventManager.h>
#include <Log.h>
#include "raygui.h"

struct LoadBallsEvent
{
	std::string msg = "BallScene loaded";
};

class BallsScene:
	public SceneBase
{
public:
	BallsScene();
	void Load() override;
	void UnLoad() override;
	void Update() override;
	void Draw() override;
	void PressButton() override;
	void EventLoadMsg(const LoadBallsEvent& m);
	bool showMsg = false;
	Rectangle rectangle = { 24, 24, 120, 30 };

	
private:
	std::vector<Ball*> bolitas;
	Rectangle button;

	
};


