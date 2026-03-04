#pragma once
#include "raylib.h"
#include "SceneBase.h"
#include "Ball.h"
#include <vector>
#include <map>
#include <EventManager.h>
#include <Log.h>
#include <memory>
#include "raygui.h"
#include "ResourceManager.h"
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
	Rectangle rectangle2 = { 24, 24, 240, 120 };

	BodyData boxDef;


	
	
private:
	std::vector<Ball*> bolitas;
	Rectangle button;
	Texture2D texPrueba;
	std::shared_ptr<Music> music;
	std::shared_ptr<Texture2D> texture;
	std::shared_ptr<PCircle> pivot;
	std::shared_ptr<PCircle> pivot2;
	std::shared_ptr<PCircle> cir;

	std::vector<std::shared_ptr<JointData>> jointsVector;

	Vector2 lineStartPos;
	bool isDrawingLine = false;
	
	void onCollision(const CollisionEvent& event);


	
};



