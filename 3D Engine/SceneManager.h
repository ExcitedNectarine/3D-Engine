#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include <glm/glm.hpp>
#include "EntityManager.h"
#include "LightManager.h"

namespace ENG
{
	class Application;
	//class EntityManager;
	//class LightManager;

	class BaseScene
	{
	public:
		BaseScene(Application& app);

		virtual void update(const float delta);
		virtual void draw2D();
		virtual void draw3D();

		void setAlive(const bool alive) { this->alive = alive; }
		bool getAlive() { return alive; }

		EntityManager& getEntityManager();
		LightManager& getLightManager();

	protected:
		Application& app;
		EntityManager entities;
		LightManager lights;
		bool alive = true;
	};

	class SceneManager
	{
	public:
		SceneManager(Application& app);
		void popScene();
		BaseScene& getCurrentScene();

		void update() {
			scenes.erase(std::remove_if(scenes.begin(), scenes.end(),
				[](const std::unique_ptr<BaseScene>& scene) { return !scene->getAlive(); }
			), scenes.end());
		}

		template <typename SceneType>
		void addScene()
		{
			static_assert(std::is_base_of<BaseScene, SceneType>::value, "'SceneType' must inherit 'BaseScene'.");
			scenes.push_back(std::make_unique<SceneType>(app));
		}

	private:
		Application& app;
		std::vector<std::unique_ptr<BaseScene>> scenes;
	};
}