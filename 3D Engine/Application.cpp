#include "Application.h"

namespace ENG
{
	Application::Application()
		: scenes(*this),
		configuration("Resources/Configuration.xml")
	{
		// Get the configuration map.
		ConfigurationManager::ConfigurationMap& config = configuration.getConfigurationMap();
		int width = std::stoi(config["screen"]["width"]); // get the screen width
		int height = std::stoi(config["screen"]["height"]); // get the screen height
		int framerate = std::stoi(config["screen"]["framerate"]); // get the framerate
		int fov = std::stoi(config["screen"]["fov"]);

		// Create both projection matrices.
		perspective = glm::perspective(glm::radians(static_cast<float>(fov)), static_cast<float>(width) / height, 0.1f, 500.0f);
		orthographic = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f);
		//orthographic = glm::scale(orthographic, glm::vec3(1.0f, -1.0f, 1.0f));

		window.create(glm::ivec2(width, height), "FPS"); // create the window
		clock.setFPSLimit(framerate); // set the framerate limit

		shader_3d.create("Resources/Shaders/3d.vert", "Resources/Shaders/3d.frag");
		shader_2d.create("Resources/Shaders/2d.vert", "Resources/Shaders/2d.frag");
		unshaded.create("Resources/Shaders/unshaded.vert", "Resources/Shaders/unshaded.frag");
		shader_3d.setUniform("projection", perspective);
		shader_2d.setUniform("projection", orthographic);

		resources.loadAll("Resources/Textures");
	}

	void Application::run()
	{
		while (running)
		{
			delta = clock.update();

			if (input.update())
				running = false;

			scenes.getCurrentScene().update(delta);
			scenes.update();

			// Reset every light in the shader to get rid of lingering light sources.
			for (unsigned int i = 0; i < MAX_LIGHT_SOURCES; i++)
			{
				shader_3d.setUniform("lights[" + std::to_string(i) + "].position", glm::vec3(0.0f, 0.0f, 0.0f));
				shader_3d.setUniform("lights[" + std::to_string(i) + "].colour", glm::vec3(0.0f, 0.0f, 0.0f));
				shader_3d.setUniform("lights[" + std::to_string(i) + "].radius", 0.0f);

				shader_2d.setUniform("lights[" + std::to_string(i) + "].position", glm::vec3(0.0f, 0.0f, 0.0f));
				shader_2d.setUniform("lights[" + std::to_string(i) + "].colour", glm::vec3(0.0f, 0.0f, 0.0f));
				shader_2d.setUniform("lights[" + std::to_string(i) + "].radius", 0.0f);
			}

			// Pass info for each light to shader.
			shader_3d.setUniform("ambient", scenes.getCurrentScene().getLightManager().getAmbient());
			shader_2d.setUniform("ambient", scenes.getCurrentScene().getLightManager().getAmbient());
			std::vector<LightSource> light_sources = scenes.getCurrentScene().getLightManager().getLightSources();
			for (unsigned int i = 0; i < light_sources.size(); i++)
			{
				shader_3d.setUniform("lights[" + std::to_string(i) + "].position", light_sources[i].position);
				shader_3d.setUniform("lights[" + std::to_string(i) + "].colour", light_sources[i].colour);
				shader_3d.setUniform("lights[" + std::to_string(i) + "].radius", light_sources[i].radius);

				shader_2d.setUniform("lights[" + std::to_string(i) + "].position", light_sources[i].position);
				shader_2d.setUniform("lights[" + std::to_string(i) + "].colour", light_sources[i].colour);
				shader_2d.setUniform("lights[" + std::to_string(i) + "].radius", light_sources[i].radius);
			}

			shader_2d.setUniform("player", player_pos);
			
			window.clear(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

			// Set the projection and the view for 3D drawing.
			unshaded.setUniform("projection", perspective);
			unshaded.setUniform("view", glm::inverse(active_camera->getTransform()));
			shader_3d.setUniform("view", glm::inverse(active_camera->getTransform()));
			scenes.getCurrentScene().draw3D();
			
			// Set the projection and the view for 2D drawing.
			unshaded.setUniform("projection", orthographic);
			unshaded.setUniform("view", glm::mat4(1.0f));
			shader_2d.setUniform("view", glm::mat4(1.0f));
			scenes.getCurrentScene().draw2D();
			
			window.display();
			window.setTitle("FPS - " + std::to_string(clock.getCurrentFPS()));
		}
	}

	void Application::quit()
	{
		running = false;
	}

	void Application::draw3D(Drawable& drawable, const bool shaded)
	{
		if (shaded)
			drawable.draw(shader_3d);
		else
			drawable.draw(unshaded);
	}

	void Application::draw2D(Drawable& drawable, const bool shaded)
	{
		if (shaded)
			drawable.draw(shader_2d);
		else
			drawable.draw(unshaded);
	}

	Window& Application::getWindow()
	{
		return window;
	}

	Input& Application::getInput()
	{
		return input;
	}

	SceneManager& Application::getSceneManager()
	{
		return scenes;
	}

	ResourceManager& Application::getResourceManager()
	{
		return resources;
	}

	ConfigurationManager& Application::getConfigurationManager()
	{
		return configuration;
	}

	Transformable3D* Application::getActiveCamera() const
	{
		return active_camera;
	}

	void Application::setActiveCamera(Transformable3D* camera)
	{
		active_camera = camera;
	}
}