#include "SceneManager.h"
#include "EntityManager.h"
#include "LightManager.h"

namespace ENG
{
	BaseScene::BaseScene(Application& app)
		: app(app), entities(app, this), lights(glm::vec3(0.0f, 0.0f, 0.0f))
	{
	}

	void BaseScene::update(const float delta) { entities.update(delta); }
	void BaseScene::draw2D() { entities.draw2D(); }
	void BaseScene::draw3D() { entities.draw3D(); }
	EntityManager& BaseScene::getEntityManager() { return entities; }
	LightManager& BaseScene::getLightManager() { return lights; }

	SceneManager::SceneManager(Application& app)
		: app(app)
	{
	}

	void SceneManager::popScene()
	{
		scenes.pop_back();
	}

	BaseScene& SceneManager::getCurrentScene()
	{
		return *scenes.back();
	}
}