#pragma once
#include <string>
#include "EventManager.h"



class SceneBase
{

public:
	EventManager& eventManager = EventManager::instance();
	virtual ~SceneBase() = default;
	virtual void Load() = 0;
	virtual void UnLoad() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void PressButton() = 0;

	bool buttonPressed;
	std::string Name;
private:

};

