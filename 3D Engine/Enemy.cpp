#include "Enemy.h"
#include "Application.h"

Enemy::Enemy(ENG::Application& app, ENG::BaseScene* scene)
	: ENG::BaseEntity(app, scene)
{
	rect.size = glm::vec3(0.5f, 0.5f, 0.5f);

	walking.setAnimated(true);
	walking.setFrames(glm::vec2(2, 1));
	walking.setFrameTime(0.3f);
	walking.setBillboard(true, app.getActiveCamera());
	walking.setTexture(app.getResourceManager().getTexture("Enemy.png"));
	walking.setPosition(glm::vec3(0.0f, (static_cast<float>(walking.getTexture()->getSize().y) / 100.0f) - 1, 0.0f));

	shoot.setBillboard(true, app.getActiveCamera());
	shoot.setTexture(app.getResourceManager().getTexture("EnemyShoot.png"));
	shoot.setPosition(glm::vec3(0.0f, (static_cast<float>(walking.getTexture()->getSize().y) / 100.0f) - 1, 0.0f));

	dead.setBillboard(true, app.getActiveCamera());
	dead.setTexture(app.getResourceManager().getTexture("EnemyDeath.png"));
	dead.setPosition(glm::vec3(0.0f, (static_cast<float>(dead.getTexture()->getSize().y) / 100.0f) - 1, 0.0f));

	current = &walking;

	player = scene->getEntityManager().getEntities<Player>()[0];
}

void Enemy::update(const float delta)
{
	direction = glm::normalize(player->getPosition() - getPosition());

	switch (state)
	{
	case States::WALKING:
		walkingUpdate(delta);
		break;
	case States::SHOOTING:
		shootingUpdate(delta);
		break;
	case States::DEAD:
		break;
	}

	current->update(delta);
}

void Enemy::walkingUpdate(const float delta)
{
	velocity = direction * speed;

	projectiles = scene->getEntityManager().getEntities<Projectile>();
	for (std::shared_ptr<Projectile>& proj : projectiles)
	{
		if (ENG::Tools::Collision::AABBTest(rect, proj->getRect()))
		{
			proj->setAlive(false);

			state = States::DEAD;
			current = &dead;
		}
	}

	solids = scene->getEntityManager().getEntities<Level>()[0]->getSurroundingSolids(getPosition());
	solids.push_back(player->getRect());

	other_enemies = scene->getEntityManager().getEntities<Enemy>();
	for (std::shared_ptr<Enemy>& enemy : other_enemies)
		if (!(rect == enemy->getRect()) && !enemy->isDead())
			solids.push_back(enemy->getRect());

	// MOVEMENT AND COLLISION
	rect.position = getPosition();
	rect.position.x += velocity.x * delta;
	for (ENG::Tools::Collision::AABB& solid : solids)
	{
		if (ENG::Tools::Collision::AABBTest(rect, solid))
		{
			if (velocity.x > 0.0f)
				rect.position.x = (solid.position.x - (solid.size.x / 2.0f)) - (rect.size.x / 2.0f);
			else if (velocity.x < 0.0f)
				rect.position.x = (solid.position.x + (solid.size.x / 2.0f)) + (rect.size.x / 2.0f);
		}
	}
	rect.position.z += velocity.z * delta;
	for (ENG::Tools::Collision::AABB& solid : solids)
	{
		if (ENG::Tools::Collision::AABBTest(rect, solid))
		{
			if (velocity.z > 0.0f)
				rect.position.z = (solid.position.z - (solid.size.z / 2.0f)) - (rect.size.z / 2.0f);
			else if (velocity.z < 0.0f)
				rect.position.z = (solid.position.z + (solid.size.z / 2.0f)) + (rect.size.z / 2.0f);
		}
	}
	setPosition(rect.position);

	if (!ENG::Tools::randomInt(0, 200))
	{
		state = States::SHOOTING;
		current = &shoot;
	}
}

void Enemy::shootingUpdate(const float delta)
{
	shoot_timer += delta;
	if (shoot_timer >= shoot_time)
	{
		// create projectile
		scene->getEntityManager().addEntity<EnemyProjectile>(
			direction
		)->setPosition(getPosition());

		state = States::WALKING;
		shoot_timer = 0.0f;
		current = &walking;
	}
}

ENG::Tools::Collision::AABB Enemy::getRect()
{
	return rect;
}


void Enemy::draw3D()
{
	current->setPosition(glm::vec3(getPosition().x, current->getPosition().y, getPosition().z));
	app.draw3D(*current);
}