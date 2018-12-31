#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(ENG::Application& app)
	: ENG::BaseScene(app)
{
	app.getInput().setCaptureMouse(false);

	play = entities.addEntity<Button>(app.getResourceManager().getTexture("PlayButton.png"));
	play->setPosition(glm::vec3(app.getWindow().getSize().x / 2.0f, app.getWindow().getSize().y / 2.0f, 0.0f));
	exit = entities.addEntity<Button>(app.getResourceManager().getTexture("ExitButton.png"));
	exit->setPosition(glm::vec3(app.getWindow().getSize().x / 2.0f, (app.getWindow().getSize().y / 2.0f) + 50.0f, 0.0f));
}

void MainMenuScene::update(const float delta)
{
	entities.update(delta);

	if (play->isPressed())
		app.getSceneManager().addScene<GameScene>();

	if (exit->isPressed())
		app.quit();
}