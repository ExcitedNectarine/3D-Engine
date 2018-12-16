#include "Window.h"
#include "Clock.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sprite.h"
#include "Input.h"
#include "Application.h"
#include "Player.h"
#include "Level.h"
#include "Enemy.h"
#include "Prop.h"

class NewScene : public ENG::BaseScene
{
public:
	NewScene(ENG::Application& app) : ENG::BaseScene(app)
	{
		auto level = entities.addEntity<Level>();
		level->load("Resources/Levels/Level.xml");
		auto p = entities.addEntity<Player>();
		p->setPosition(level->getObjects(1)[0].position);
		lights.setAmbient(glm::vec3(0.5f, 0.5f, 0.5f));

		for (ENG::Tools::Collision::AABB& rect : level->getObjects(2))
			entities.addEntity<Enemy>()->setPosition(rect.position);

		for (ENG::Tools::Collision::AABB& rect : level->getObjects(3))
			entities.addEntity<Prop>(app.getResourceManager().getTexture("Light.png"), glm::vec3(3.0f, 3.0f, 2.8f), 4.0f)->setPosition(rect.position);
	}

	void update(const float delta)
	{
		entities.update(delta);

		if (app.getInput().isKeyPressed(SDL_SCANCODE_ESCAPE))
			app.quit();
	}
};

int main(int argc, char* argv[])
{
	try
	{
		ENG::Application app;
		app.getSceneManager().addScene<NewScene>();
		app.run();
	}
	catch (const ENG::ApplicationException& error)
	{
		OUTPUT_ERROR(error.what());
		std::cin.get();
	}

	return 0;
}