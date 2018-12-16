#pragma once

#include "EntityManager.h"
#include "Sprite.h"
#include "Player.h"
#include "Level.h"

class Enemy : public ENG::BaseEntity
{
public:
	Enemy(ENG::Application& app, ENG::BaseScene* scene);
	void update(const float delta);
	ENG::Tools::Collision::AABB getRect();
	void draw3D();

private:
	glm::vec3 direction;
	glm::vec3 velocity;
	float speed = 1.0f;

	ENG::Sprite3D sprite;
	ENG::Tools::Collision::AABB rect;
	std::vector<ENG::Tools::Collision::AABB> solids;
	std::shared_ptr<Player> player;
};