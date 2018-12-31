#pragma once

#include "SceneManager.h"
#include "GameScene.h"
#include "Button.h"

class MainMenuScene : public ENG::BaseScene
{
public:
	MainMenuScene(ENG::Application& app);
	void update(const float delta);

private:
	std::shared_ptr<Button> play;
	std::shared_ptr<Button> exit;
};