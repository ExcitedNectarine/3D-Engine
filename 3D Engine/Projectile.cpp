#include "Projectile.h"

Projectile::Projectile(ENG::Application& app, ENG::BaseScene* scene, const glm::vec3& direction)
	: ENG::BaseEntity(app, scene), direction(direction)
{
	sprite.setTexture(app.getResourceManager().getTexture("Shot2.png"));
	sprite.setBillboard(true, app.getActiveCamera());
	rect.size = glm::vec3(0.3f, 0.3f, 0.3f);
	light = scene->getLightManager().add(getPosition(), glm::vec3(1.0f, 2.0f, 2.0f), 1.5f);
}

void Projectile::update(const float delta)
{
	sprite.update(delta);
	moveBy(direction * speed * delta);
	solids = scene->getEntityManager().getEntities<Level>()[0]->getSurroundingSolids(getPosition());
	rect.position = getPosition() - (rect.size / 2.0f);
	for (ENG::Tools::Collision::AABB& solid : solids)
	{
		solid.position -= solid.size / 2.0f;
		if (ENG::Tools::Collision::AABBTest(rect, solid))
		{
			setAlive(false);
			scene->getLightManager().remove(light);
		}
	}

	scene->getLightManager().setPosition(light, getPosition());
}

void Projectile::draw3D()
{
	sprite.setPosition(getPosition());
	app.draw3D(sprite);
}