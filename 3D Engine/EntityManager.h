#pragma once

#include <list>
#include <vector>
#include <memory>
#include "Drawable.h"
#include "Transformable.h"

namespace ENG
{
	class Application;
	class BaseScene;

	class BaseEntity : public ENG::Transformable3D, public ENG::Drawable
	{
	public:
		BaseEntity(Application& app, BaseScene* scene) : app(app), scene(scene) {}
		virtual void update(const float delta) {}

		virtual void draw2D() {}
		virtual void draw3D() {}

		void setAlive(const bool alive) { this->alive = alive; }
		bool getAlive() { return alive; }

	protected:
		Application& app;
		BaseScene* scene;
		bool alive = true;
	};

	class EntityManager
	{
	public:
		EntityManager(Application& app, BaseScene* scene);
		void update(const float delta);

		void draw3D() const;
		void draw2D() const;

		template <typename EntityType, typename ...Args>
		std::shared_ptr<EntityType> addEntity(Args&& ...args)
		{
			// make sure the entity type inherits from base entity
			static_assert(std::is_base_of<BaseEntity, EntityType>::value, "'EntityType' must inherit 'BaseEntity'.");

			// add the entity to the list, passing the app and the scene to its constructor
			entities.push_back(std::make_shared<EntityType>(app, scene, std::forward<Args>(args)...));

			// return a casted pointer
			return std::dynamic_pointer_cast<EntityType>(entities.back());
		}

		template <typename EntityType>
		std::vector<std::shared_ptr<EntityType>> getEntities()
		{
			// make sure the entity type inherits from base entity
			static_assert(std::is_base_of<BaseEntity, EntityType>::value, "'EntityType' must inherit 'BaseEntity'.");
			std::vector<std::shared_ptr<EntityType>> entity_pointers;
			for (std::shared_ptr<BaseEntity> entity : entities)
				if (typeid(*entity) == typeid(EntityType))
					entity_pointers.push_back(std::dynamic_pointer_cast<EntityType>(entity));
			return entity_pointers;
		}

	private:
		Application& app;
		BaseScene* scene;
		mutable std::list<std::shared_ptr<BaseEntity>> entities;
	};
}