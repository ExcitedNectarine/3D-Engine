#include "Player.h"
#include "Application.h"
#include "Enemy.h"

Player::Player(ENG::Application& app, ENG::BaseScene* scene)
	: ENG::BaseEntity(app, scene)
{
	app.setActiveCamera(this);
	rect.size = glm::vec3(1.0f, 1.0f, 1.0f);

	gun.setAnimated(true);
	gun.setFrames(glm::vec2(2, 1));
	gun.setFrameTime(shoot_time / 2.0f);
	gun.setTexture(app.getResourceManager().getTexture("Gun.png"));
	gun.setPosition(glm::vec2(app.getWindow().getSize().x / 2, 0.0f));
	gun.moveBy(glm::vec2(75.0f, 0.0f));

	heart.setTexture(app.getResourceManager().getTexture("Heart.png"));

	crosshair.setTexture(app.getResourceManager().getTexture("Crosshair.png"));
	crosshair.setOrigin(glm::vec2(crosshair.getTexture()->getSize()) / 2.0f);
	crosshair.setPosition(glm::vec2(app.getWindow().getSize()) / 2.0f);

	level = scene->getEntityManager().getEntities<Level>()[0];
}

void Player::update(const float delta)
{
	app.player_pos = getPosition();
	rotateBy(glm::vec3(0.0f, -app.getInput().getMouseOffset().y * sensitivity, 0.0f));
	//rotateBy(glm::vec3(-app.getInput().getMouseOffset() * sensitivity, 0.0f));

	direction = glm::vec3(0.0f, 0.0f, 0.0f);
	if (app.getInput().isKeyPressed(SDL_SCANCODE_W))
		direction -= getForward();
	else if (app.getInput().isKeyPressed(SDL_SCANCODE_S))
		direction += getForward();
	if (app.getInput().isKeyPressed(SDL_SCANCODE_A))
		direction -= getRight();
	else if (app.getInput().isKeyPressed(SDL_SCANCODE_D))
		direction += getRight();

	if (direction != glm::vec3(0.0f, 0.0f, 0.0f))
		direction = glm::normalize(direction);

	velocity.x = direction.x * speed;
	velocity.z = direction.z * speed;

	solids = level->getSurroundingSolids(getPosition());
	for (std::shared_ptr<Enemy> enemy : scene->getEntityManager().getEntities<Enemy>())
		if (!enemy->isDead()) solids.push_back(enemy->getRect());

	rect.position = getPosition();
	rect.position.x += velocity.x * delta;
	for (ENG::Tools::Collision::AABB& solid : solids)
	{
		if (ENG::Tools::Collision::AABBTest(rect, solid))
		{
			if (velocity.x > 0.0f)
				rect.position.x = (solid.position.x - (solid.size.x / 2.0f)) - (rect.size.x / 2.0f);
			else if (velocity.x < 0.0f)
				rect.position.x = (solid.position.x + (solid.size.x / 2.0f)) + (rect.size.x / 2.0f);
		}
	}
	rect.position.z += velocity.z * delta;
	for (ENG::Tools::Collision::AABB& solid : solids)
	{
		if (ENG::Tools::Collision::AABBTest(rect, solid))
		{
			if (velocity.z > 0.0f)
				rect.position.z = (solid.position.z - (solid.size.z / 2.0f)) - (rect.size.z / 2.0f);
			else if (velocity.z < 0.0f)
				rect.position.z = (solid.position.z + (solid.size.z / 2.0f)) + (rect.size.z / 2.0f);
		}
	}
	setPosition(rect.position);

	if (shooting)
	{
		gun.update(delta);
		shoot_timer += delta;
		if (shoot_timer >= shoot_time)
		{
			scene->getEntityManager().addEntity<Projectile>(
				glm::normalize(-getForward())
			)->setPosition(getPosition());

			shoot_timer = 0.0f;
		}
	}

	if (app.getInput().isMouseButtonPressed(SDL_BUTTON_LEFT) && !shooting)
	{
		shooting = true;
		
		scene->getEntityManager().addEntity<Projectile>(
			glm::normalize(-getForward())
		)->setPosition(getPosition());

		gun.setFrame(glm::vec2(2, 1));
	}

	else if (!app.getInput().isMouseButtonPressed(SDL_BUTTON_LEFT) && shooting)
	{
		shooting = false;
		shoot_timer = 0.0f;
		gun.setFrame(glm::vec2(1, 1));
	}

	projectiles = scene->getEntityManager().getEntities<EnemyProjectile>();
	for (std::shared_ptr<EnemyProjectile>& proj : projectiles)
	{
		if (ENG::Tools::Collision::AABBTest(rect, proj->getRect()))
		{
			proj->setAlive(false);
			if (--hp == 0)
				app.quit();
		}
	}
}

ENG::Tools::Collision::AABB Player::getRect()
{
	return rect;
}

void Player::draw2D()
{
	app.draw2D(gun);
	app.draw2D(crosshair);

	for (int i = 0; i < hp; i++)
	{
		heart.setPosition(glm::vec2((i * heart.getTexture()->getSize().x) + 20.0f, 20.0f));
		app.draw2D(heart);
	}
}