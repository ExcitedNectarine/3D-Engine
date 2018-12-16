#include "Window.h"

namespace ENG
{
	Window::Window(const glm::ivec2& size, const std::string& title)
	{
		create(size, title);
	}

	Window::Window()
	{
	}

	void Window::create(const glm::ivec2& size, const std::string& title)
	{
		this->size = size;
		this->title = title;

		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw ApplicationException("Failed to initialize SDL.");

		window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			size.x,
			size.y,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
		);

		if (!window)
			throw ApplicationException("Failed to create window.");

		if (!SDL_GL_CreateContext(window))
			throw ApplicationException("Failed to create GL context.");

		if (glewInit() != GLEW_OK)
			throw ApplicationException("Failed to initialize GLEW.");

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Window::clear(const glm::vec4& colour)
	{
		glClearColor(colour.x, colour.y, colour.z, colour.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::display()
	{
		SDL_GL_SwapWindow(window);
	}

	glm::ivec2 Window::getSize() const
	{
		return size;
	}

	void Window::setSize(const glm::ivec2& size)
	{
		this->size = size;
		SDL_SetWindowSize(window, size.x, size.y);
	}

	std::string Window::getTitle() const
	{
		return title;
	}

	void Window::setTitle(const std::string& title)
	{
		this->title = title;
		SDL_SetWindowTitle(window, title.c_str());
	}

	SDL_Window* Window::getHandle()
	{
		return window;
	}


	Window::~Window()
	{
		SDL_DestroyWindow(window);
	}
}