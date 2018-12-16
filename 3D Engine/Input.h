#pragma once

#include <SDL.h>
#include <glm/glm.hpp>

namespace ENG
{
	class Input
	{
	public:
		void setCaptureMouse(const bool capture);
		bool isMouseCaptured();
		bool update();
		bool isKeyPressed(SDL_Scancode key) const;
		bool isMouseButtonPressed(Uint8 button) const;
		glm::vec2 getMousePosition() const;
		glm::vec2 getMouseOffset() const;

	private:
		SDL_Event event;
		glm::vec2 mouse_position;
		glm::vec2 mouse_offset;
		const Uint8* keys = nullptr;
	};
}