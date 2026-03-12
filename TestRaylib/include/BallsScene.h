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
#include "sol/sol.hpp"

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
	Rectangle button;
	Texture2D texPrueba;
	std::shared_ptr<Music> music;
	std::shared_ptr<Texture2D> texture;
	std::shared_ptr<PCircle> pivot;
	std::shared_ptr<PCircle> pivot2;
	std::shared_ptr<PCircle> cir;

	bool isWin = false;
	bool isDefeat = false;
	std::vector<std::shared_ptr<JointData>> jointsVector;

	Vector2 lineStartPos;
	bool isDrawingLine = false;

	void BindRayLib();
	
	sol::state lua;
	sol::function luaUpdate;
	sol::function luaDraw;

	void onCollision(const CollisionEvent& event);




	
};



