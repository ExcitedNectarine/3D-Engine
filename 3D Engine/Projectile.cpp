#include "Projectile.h"

Projectile::Projectile(ENG::Application& app, ENG::BaseScene* scene, const glm::vec3& direction)
	: ENG::BaseEntity(app, scene), direction(direction)
{
	sprite.setAnimated(true);
	sprite.setFrames(glm::vec2(2, 1));
	sprite.setFrameTime(0.2f);
	sprite.setTexture(app.getResourceManager().getTexture("Shot.png"));
	sprite.setBillboard(true, app.getActiveCamera());

	rect.size = glm::vec3(0.3f, 0.3f, 0.3f);
	light = scene->getLightManager().add(getPosition(), glm::vec3(2.0f, 2.0f, 4.0f) , 1.5f);
}

void Projectile::update(const float delta)
{
	sprite.update(delta);

	moveBy(direction * speed * delta);
	solids = scene->getEntityManager().getEntities<Level>()[0]->getSurroundingSolids(getPosition());
	rect.position = getPosition();

	for (ENG::Tools::Collision::AABB& solid : solids)
	{
		if (ENG::Tools::Collision::AABBTest(rect, solid))
			setAlive(false);
	}

	scene->getLightManager().setPosition(light, getPosition());
}

ENG::Tools::Collision::AABB Projectile::getRect()
{
	return rect;
}

void Projectile::setAlive(const bool alive)
{
	ENG::BaseEntity::setAlive(alive);
	scene->getLightManager().remove(light);
}

void Projectile::draw3D()
{
	sprite.setPosition(getPosition());
	app.draw3D(sprite);
}