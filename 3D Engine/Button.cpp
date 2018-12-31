#include "Button.h"
#include "Application.h"

Button::Button(ENG::Application& app, ENG::BaseScene* scene, ENG::Texture* texture)
	: ENG::BaseEntity(app, scene)
{
	sprite.setTexture(texture);
	sprite.setOrigin(glm::vec2(texture->getSize()) / 2.0f);
}

void Button::update(const float delta)
{
	if (pressed)
		pressed = false;

	if (app.getInput().isMouseButtonPressed(SDL_BUTTON_LEFT))
	{
		SDL_Point mouse;
		mouse.x = app.getInput().getMousePosition().x;
		mouse.y = app.getInput().getMousePosition().y;

		SDL_Rect rect;
		rect.w = sprite.getTexture()->getSize().x;
		rect.h = sprite.getTexture()->getSize().y;
		rect.x = sprite.getPosition().x;
		rect.y = sprite.getPosition().y;

		if (SDL_PointInRect(&mouse, &rect))
			pressed = true;
	}
}

void Button::draw2D()
{
	sprite.setPosition(glm::vec2(getPosition()));
	app.draw2D(sprite, false);
}