#include "Prop.h"

Prop::Prop(ENG::Application& app, ENG::BaseScene* scene, ENG::Texture* texture, const glm::vec3& colour, const float radius)
	: ENG::BaseEntity(app, scene)
{
	sprite.setTexture(texture);
	sprite.setBillboard(true, app.getActiveCamera());
	sprite.setPosition(glm::vec3(0.0f, (static_cast<float>(texture->getSize().y) / 100.0f) - 1, 0.0f));
	light = scene->getLightManager().add(getPosition(), colour, radius);
}

void Prop::draw3D()
{
	sprite.setPosition(glm::vec3(getPosition().x, sprite.getPosition().y, getPosition().z));
	scene->getLightManager().setPosition(light, getPosition());
	app.draw3D(sprite);
}