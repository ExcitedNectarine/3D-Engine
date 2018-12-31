#pragma once

#include <SDL.h>
#include <glm/glm.hpp>
#include "Output.h"

namespace ENG
{
	class Input
	{
	public:
		Input() : mouse_position(0.0f, 0.0f), mouse_offset(0.0f, 0.0f) {}
		void setCaptureMouse(const bool capture);
		bool isMouseCaptured();
		bool update();
		bool isKeyPressed(SDL_Scancode key) const;
		bool isMouseButtonPressed(Uint8 button) const;
		glm::ivec2 getMousePosition() const;
		glm::vec2 getMouseOffset() const;

	private:
		SDL_Event event;
		glm::ivec2 mouse_position;
		glm::vec2 mouse_offset;
		const Uint8* keys = nullptr;
	};
}