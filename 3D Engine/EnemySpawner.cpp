#include "EnemySpawner.h"
#include "Application.h"

EnemySpawner::EnemySpawner(ENG::Application& app, ENG::BaseScene* scene)
	: ENG::BaseEntity(app, scene)
{
	sprite.setAnimated(true);
	sprite.setTexture(app.getResourceManager().getTexture("EnemySpawner.png"));
	sprite.setFrames(glm::vec2(2, 1));
	sprite.setBillboard(true, app.getActiveCamera());
	sprite.setFrameTime(0.1f);

	light = scene->getLightManager().add(getPosition(), glm::vec3(5.0f, 5.0f, 5.0f), 5);
}

void EnemySpawner::update(const float delta)
{
	sprite.update(delta);

	spawn_timer += delta;
	if (spawn_timer >= spawn_time)
	{
		spawn_timer = 0.0f;
		scene->getEntityManager().addEntity<Enemy>()->setPosition(getPosition());
	}

	scene->getLightManager().setPosition(light, getPosition());
}

void EnemySpawner::draw3D()
{
	sprite.setPosition(getPosition());
	app.draw3D(sprite);
}