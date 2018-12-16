#include "Enemy.h"
#include "Application.h"

Enemy::Enemy(ENG::Application& app, ENG::BaseScene* scene)
	: ENG::BaseEntity(app, scene)
{
	rect.size = glm::vec3(0.1f, 1.0f, 0.1f);

	sprite.setAnimated(true);
	sprite.setFrames(glm::vec2(2, 1));
	sprite.setFrameTime(0.3f);
	sprite.setBillboard(true, app.getActiveCamera());
	sprite.setTexture(app.getResourceManager().getTexture("Enemy.png"));
	sprite.setPosition(glm::vec3(0.0f, (static_cast<float>(sprite.getTexture()->getSize().y) / 100.0f) - 1, 0.0f));

	player = scene->getEntityManager().getEntities<Player>()[0];
}

void Enemy::update(const float delta)
{
	sprite.update(delta);

	direction = glm::normalize(player->getPosition() - getPosition());
	velocity = direction * speed;

	solids = scene->getEntityManager().getEntities<Level>()[0]->getSurroundingSolids(getPosition());
	solids.push_back(player->getRect());

	rect.position = getPosition() - (rect.size / 2.0f);
	rect.position.x += velocity.x * delta;
	for (ENG::Tools::Collision::AABB& solid : solids)
	{
		solid.position -= solid.size / 2.0f;
		if (ENG::Tools::Collision::AABBTest(rect, solid))
		{
			if (velocity.x > 0.0f)
				rect.position.x = solid.position.x - rect.size.x;
			else if (velocity.x < 0.0f)
				rect.position.x = solid.position.x + solid.size.x;
		}
	}
	rect.position.z += velocity.z * delta;
	for (ENG::Tools::Collision::AABB& solid : solids)
	{
		solid.position -= solid.size / 2.0f;
		if (ENG::Tools::Collision::AABBTest(rect, solid))
		{
			if (velocity.z > 0.0f)
				rect.position.z = solid.position.z - rect.size.z;
			else if (velocity.z < 0.0f)
				rect.position.z = solid.position.z + solid.size.z;
		}
	}
	setPosition(rect.position + (rect.size / 2.0f));
}

ENG::Tools::Collision::AABB Enemy::getRect()
{
	return rect;
}


void Enemy::draw3D()
{
	sprite.setPosition(glm::vec3(getPosition().x, sprite.getPosition().y, getPosition().z));
	app.draw3D(sprite);
}