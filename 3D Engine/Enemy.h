#pragma once

#include "EntityManager.h"
#include "Sprite.h"
#include "Player.h"
#include "Level.h"
#include "Projectile.h"
#include "EnemyProjectile.h"

class Enemy : public ENG::BaseEntity
{
public:
	Enemy(ENG::Application& app, ENG::BaseScene* scene);
	void update(const float delta);
	ENG::Tools::Collision::AABB getRect();
	void draw3D();
	bool isDead() { return state == States::DEAD; }

private:
	void walkingUpdate(const float delta);
	void shootingUpdate(const float delta);

private:
	enum class States
	{
		WALKING,
		SHOOTING,
		DEAD
	};
	States state = States::WALKING;

	int hp = 3;

	glm::vec3 direction;
	glm::vec3 velocity;
	float speed = 1.0f;

	float shoot_timer = 0.0f;
	float shoot_time = 0.5f;

	ENG::Sprite3D* current;
	ENG::Sprite3D walking;
	ENG::Sprite3D shoot;
	ENG::Sprite3D dead;

	ENG::Tools::Collision::AABB rect;
	std::vector<ENG::Tools::Collision::AABB> solids;
	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<Projectile>> projectiles;
	std::vector<std::shared_ptr<Enemy>> other_enemies;
};