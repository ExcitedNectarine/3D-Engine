#pragma once

#include "Application.h"
#include "EntityManager.h"
#include "Sprite.h"

class Prop : public ENG::BaseEntity
{
public:
	Prop(ENG::Application& app, ENG::BaseScene* scene, ENG::Texture* texture, const glm::vec3& colour, const float radius);
	void draw3D();

private:
	ENG::Sprite3D sprite;
	uint16_t light;
};