#pragma once

#include "Application.h"
#include "Sprite.h"
#include "Level.h"
#include "EntityManager.h"

class EnemyProjectile : public ENG::BaseEntity
{
public:
	EnemyProjectile(ENG::Application& app, ENG::BaseScene* scene, const glm::vec3& direction);
	void setAlive(const bool alive);
	void update(const float delta);
	ENG::Tools::Collision::AABB getRect();
	void draw3D();

private:
	ENG::Sprite3D sprite;
	ENG::Tools::Collision::AABB rect;
	glm::vec3 direction;
	std::vector<ENG::Tools::Collision::AABB> solids;
	uint16_t light;
	float speed = 10.0f;
};