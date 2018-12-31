#pragma once

#include "SceneManager.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Prop.h"
#include "EnemySpawner.h"

class GameScene : public ENG::BaseScene
{
public:
	GameScene(ENG::Application& app);
	void update(const float delta);
};