#pragma once

#include "Application.h"
#include "Sprite.h"
#include "Level.h"
#include "EntityManager.h"

class Projectile : public ENG::BaseEntity
{
public:
	Projectile(ENG::Application& app, ENG::BaseScene* scene, const glm::vec3& direction);
	void update(const float delta);
	void draw3D();

private:
	ENG::Sprite3D sprite;
	ENG::Tools::Collision::AABB rect;
	glm::vec3 direction;
	std::vector<ENG::Tools::Collision::AABB> solids;
	uint16_t light;
	float speed = 10.0f;
};