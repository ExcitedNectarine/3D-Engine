#pragma once

#include "EntityManager.h"
#include "Sprite.h"

class Button : public ENG::BaseEntity
{
public:
	Button(ENG::Application& app, ENG::BaseScene* scene, ENG::Texture* texture);
	void update(const float delta);
	void draw2D();
	bool isPressed() { return pressed; }

private:
	ENG::Sprite2D sprite;
	bool pressed = false;
};