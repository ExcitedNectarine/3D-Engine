#include "Input.h"

namespace ENG
{
	void Input::setCaptureMouse(const bool capture)
	{
		SDL_SetRelativeMouseMode(SDL_bool(capture));
	}

	bool Input::isMouseCaptured()
	{
		return SDL_GetRelativeMouseMode();
	}

	bool Input::update()
	{
		mouse_offset = glm::vec2(0.0f, 0.0f);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				return true;

			if (event.type == SDL_MOUSEMOTION)
				mouse_offset = glm::vec2(event.motion.yrel, event.motion.xrel);
		}

		SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
		keys = SDL_GetKeyboardState(nullptr);

		return false;
	}

	bool Input::isKeyPressed(SDL_Scancode key) const
	{
		return keys[key];
	}

	bool Input::isMouseButtonPressed(Uint8 button) const
	{
		return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button);
	}

	glm::ivec2 Input::getMousePosition() const
	{
		return mouse_position;
	}

	glm::vec2 Input::getMouseOffset() const
	{
		return mouse_offset;
	}
}