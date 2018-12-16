#include "EntityManager.h"
#include "Application.h"

namespace ENG
{
	EntityManager::EntityManager(Application& app, BaseScene* scene)
		: app(app), scene(scene)
	{
	}

	void EntityManager::update(const float delta)
	{
		// update all entities
		for (std::shared_ptr<BaseEntity>& entity : entities)
			entity->update(delta);

		// remove all entities that died this frame
		entities.remove_if(
			[](const std::shared_ptr<BaseEntity>& entity) { return !entity->getAlive(); }
		);
	}

	void EntityManager::draw3D() const
	{
		for (std::shared_ptr<BaseEntity>& entity : entities)
		{
			app.draw3D(*entity);
			entity->draw3D();
		}
	}

	void EntityManager::draw2D() const
	{
		for (const std::shared_ptr<BaseEntity>& entity : entities)
			entity->draw2D();
	}
}