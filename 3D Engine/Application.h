#pragma once

#include "Window.h"
#include "Clock.h"
#include "Input.h"
#include "ShaderProgram.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "ConfigurationManager.h"
#include "LightManager.h"
#include "Output.h"
#include "Transformable.h"
#include "Drawable.h"

namespace ENG
{
	class Application
	{
	public:
		Application();
		void run();
		void quit();

		void draw2D(Drawable& drawable, const bool shaded = true);
		void draw3D(Drawable& drawable, const bool shaded = true);

		Window& getWindow();
		Input& getInput();

		SceneManager& getSceneManager();
		ResourceManager& getResourceManager();
		ConfigurationManager& getConfigurationManager();

		Transformable3D* getActiveCamera() const;
		void setActiveCamera(Transformable3D* camera);

		glm::vec3 player_pos;
	
	private:
		Window window;
		Clock clock;
		Input input;
		ShaderProgram shader_3d;
		ShaderProgram shader_2d;
		ShaderProgram unshaded;

		SceneManager scenes;
		ResourceManager resources;
		ConfigurationManager configuration;

		Transformable3D default_camera;
		Transformable3D* active_camera = &default_camera;

		glm::mat4 perspective;
		glm::mat4 orthographic;

		bool running = true;
		float delta = 0.0f;
	};
}