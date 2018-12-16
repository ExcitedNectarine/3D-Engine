#pragma once

#include <string>
#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ApplicationException.h"

namespace ENG
{
	class Window
	{
	public:
		Window(const glm::ivec2& size, const std::string& title);
		Window();
		~Window();
		void create(const glm::ivec2& size, const std::string& title);
		void clear(const glm::vec4& colour);
		void display();
		glm::ivec2 getSize() const;
		void setSize(const glm::ivec2& size);
		std::string getTitle() const;
		void setTitle(const std::string& title);
		SDL_Window* getHandle();

	private:
		SDL_Window * window = nullptr;
		glm::vec2 size;
		std::string title;
	};
}