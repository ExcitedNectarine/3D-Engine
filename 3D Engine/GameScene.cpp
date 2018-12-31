#include "GameScene.h"

GameScene::GameScene(ENG::Application& app) : ENG::BaseScene(app)
{
	app.getInput().setCaptureMouse(true);

	auto level = entities.addEntity<Level>();
	level->load("Resources/Levels/Level.xml");
	auto p = entities.addEntity<Player>();
	p->setPosition(level->getObjects(1)[0].position);
	lights.setAmbient(glm::vec3(0.1f, 0.1f, 0.1f));

	for (ENG::Tools::Collision::AABB& rect : level->getObjects(2))
		entities.addEntity<Enemy>()->setPosition(rect.position);

	for (ENG::Tools::Collision::AABB& rect : level->getObjects(3))
		entities.addEntity<Prop>(app.getResourceManager().getTexture("Light.png"), glm::vec3(3.0f, 3.0f, 2.8f), 4.0f)->setPosition(rect.position);

	for (ENG::Tools::Collision::AABB& rect : level->getObjects(4))
		entities.addEntity<EnemySpawner>()->setPosition(rect.position);
}

void GameScene::update(const float delta)
{
	entities.update(delta);

	if (app.getInput().isKeyPressed(SDL_SCANCODE_ESCAPE))
	{
		app.getInput().setCaptureMouse(false);
		setAlive(false);
	}
}