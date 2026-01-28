#pragma once
#include "SceneBase.h"
#include "Log.h"
class SceneManager
{
public:
	static SceneManager& instance() // Para hacer un singleton
	{
		static SceneManager instance;
		return instance;
	}
	void ChangeScene(SceneBase* newScene);
	void UpdateScene();
	void DrawScene();
	SceneBase* GetCurrentScene();
private:
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	SceneBase* currentScene;
};

