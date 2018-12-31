#pragma once

#include "EntityManager.h"
#include "Enemy.h"

class EnemySpawner : public ENG::BaseEntity
{
public:
	EnemySpawner(ENG::Application& app, ENG::BaseScene* scene);
	void update(const float delta);
	void draw3D();

private:
	ENG::Sprite3D sprite;
	uint16_t light;
	float spawn_timer = 0.0f, spawn_time = 5.0f;
};