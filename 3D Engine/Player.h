#pragma once

#include "EntityManager.h"
#include "LightManager.h"
#include "Sprite.h"
#include "Tools.h"
#include "Level.h"
#include "Projectile.h"
#include "EnemyProjectile.h"
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/compatibility.hpp>

class Player : public ENG::BaseEntity
{
public:
	Player(ENG::Application& app, ENG::BaseScene* scene);
	void update(const float delta);
	ENG::Tools::Collision::AABB getRect();
	void draw2D();
	void addHealth() { if (hp >= 0) hp++; }

private:
	float sensitivity = 0.35f;
	int hp = 5;

	float speed = 5.0f;
	glm::vec3 direction;
	glm::vec3 velocity;

	bool shooting = false;
	float shoot_timer = 0.0f;
	float shoot_time = 0.3f;

	ENG::Sprite2D gun;
	ENG::Sprite2D heart;
	ENG::Sprite2D crosshair;
	ENG::Tools::Collision::AABB rect;
	std::vector<ENG::Tools::Collision::AABB> solids;
	std::shared_ptr<Level> level;
	std::vector<std::shared_ptr<EnemyProjectile>> projectiles;
};