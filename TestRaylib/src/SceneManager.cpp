#include "SceneManager.h"

void SceneManager::ChangeScene(SceneBase* newScene)
{
	if (currentScene) //Para el cambio de la escena primero checamos si ya tenemos una escena
	{
		currentScene->UnLoad(); // Si es el caso la descargamos

		Log::print("Escena deslogeada" + currentScene->Name);
	}
	currentScene = newScene; // sustituimos la escena por la que queramos
	Log::print("Nueva escena: " + currentScene->Name);
	if (currentScene)
	{
		currentScene->Load(); // Y la cargamos
		Log::print("Load de la escena : " + currentScene->Name);
	}
}

void SceneManager::UpdateScene()
{
	currentScene->UpdateScene();
}

void SceneManager::DrawScene()
{
	currentScene->DrawScene();
}

SceneBase* SceneManager::GetCurrentScene()
{
	return currentScene;
}
