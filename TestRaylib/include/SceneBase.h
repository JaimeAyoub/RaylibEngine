#pragma once
#include <string>
#include "EventManager.h"
#include "ResourceManager.h"
#include "PhysicsSystem.h"



class SceneBase
{

public:
	std::vector<std::shared_ptr<Entity>> entities;

	EventManager& eventManager = EventManager::instance();
	ResourceManager& resourceManager = ResourceManager::instance();
	PhysicsSystem& physicsSystem = PhysicsSystem::instance();
	virtual ~SceneBase() = default;
	virtual void Load() = 0;
	virtual void UnLoad() = 0;
	virtual void Update() {
		physicsSystem.update(GetFrameTime());

		for (auto& e : entities) e->update();

		entities.erase(
			std::remove_if(entities.begin(), entities.end(),
				[](const std::shared_ptr<Entity>& e) {
					return !e->isActive();
				}),
			entities.end()
		);		
	}
	virtual void Draw() {
		for (auto& e : entities) e->draw();
	}

	virtual void Clear() {
		entities.clear();
	}
	void addEntity(std::shared_ptr<Entity> e) {
		if (e) entities.push_back(e);
	}
	virtual void PressButton() = 0;

	bool buttonPressed;
	std::string Name;
private:

};

