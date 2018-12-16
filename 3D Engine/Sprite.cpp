#include "Sprite.h"

namespace ENG
{
	Sprite3D::Sprite3D(Texture* texture)
		: frames(1, 1),
		frame(1, 1),
		frame_size(1.0f, 1.0f)
	{
		setTexture(texture);
	}

	Sprite3D::Sprite3D()
		: frames(1, 1),
		frame(1, 1),
		frame_size(1.0f, 1.0f)
	{
	}

	void Sprite3D::create()
	{
		quad = std::make_shared<VertexArray>();
		glm::vec2 size = glm::vec2(texture->getSize()) / 100.0f;

		if (animated)
		{
			size /= frames;
			updateUVs();
		}
		else
		{
			std::shared_ptr<VertexBuffer> tex_coords(new VertexBuffer);
			
			tex_coords->add(glm::vec2(0.0f, 1.0f));
			tex_coords->add(glm::vec2(1.0f, 0.0f));
			tex_coords->add(glm::vec2(0.0f, 0.0f));
			tex_coords->add(glm::vec2(0.0f, 1.0f));
			tex_coords->add(glm::vec2(1.0f, 1.0f));
			tex_coords->add(glm::vec2(1.0f, 0.0f));

			quad->setBuffer("tex_coords", tex_coords);
		}

		std::shared_ptr<VertexBuffer> positions(new VertexBuffer);
		
		positions->add(glm::vec3(-size.x, size.y, 0.0f));
		positions->add(glm::vec3(size.x, -size.y, 0.0f));
		positions->add(glm::vec3(-size.x, -size.y, 0.0f));
		positions->add(glm::vec3(-size.x, size.y, 0.0f));
		positions->add(glm::vec3(size.x, size.y, 0.0f));
		positions->add(glm::vec3(size.x, -size.y, 0.0f));

		quad->setBuffer("position", positions);
	}

	Texture* Sprite3D::getTexture() const
	{
		return texture;
	}

	void Sprite3D::setTexture(Texture* new_texture)
	{
		texture = new_texture;
		create();
	}

	void Sprite3D::draw(ShaderProgram& shader)
	{
		texture->bind();

		if (billboard)
			setRotation(glm::vec3(0.0f, camera->getRotation().y, 0.0f));
		shader.setUniform("transform", getTransform());
		shader.draw(*quad);

		texture->unbind();
	}

	bool Sprite3D::isBillboard() const
	{
		return billboard;
	}

	void Sprite3D::setBillboard(const float billboard, Transformable3D* camera)
	{
		this->camera = camera;
		this->billboard = billboard;
	}

	void Sprite3D::update(const float delta)
	{
		if (animated)
		{
			timer += delta;
			if (timer >= frame_time)
			{
				timer = 0.0f;
				if (++frame.x > frames.x)
				{
					frame.x = 1;
					if (++frame.y > frames.y)
						frame.y = 1;
				}

				updateUVs();
			}
		}
	}

	void Sprite3D::updateUVs()
	{
		std::shared_ptr<VertexBuffer> tex_coords(new VertexBuffer);

		frame_size.x = 1.0f / frames.x;
		frame_size.y = 1.0f / frames.y;

		glm::vec2 huv(frame_size.x * frame.x, frame_size.y * frame.y);
		glm::vec2 luv = huv - frame_size;

		tex_coords->add(glm::vec2(luv.x, huv.y));
		tex_coords->add(glm::vec2(huv.x, luv.y));
		tex_coords->add(glm::vec2(luv.x, luv.y));
		tex_coords->add(glm::vec2(luv.x, huv.y));
		tex_coords->add(glm::vec2(huv.x, huv.y));
		tex_coords->add(glm::vec2(huv.x, luv.y));

		quad->setBuffer("tex_coords", tex_coords);
	}

	void Sprite3D::setAnimated(const bool animate)
	{
		animated = animate;
	}

	bool Sprite3D::isAnimated() const
	{
		return animated;
	}

	void Sprite3D::setFrames(const glm::ivec2& new_frames)
	{
		frames = new_frames;
	}

	glm::ivec2 Sprite3D::getFrames() const
	{
		return frames;
	}

	void Sprite3D::setFrame(const glm::ivec2& new_frame)
	{
		frame = new_frame;
		updateUVs();
	}

	glm::ivec2 Sprite3D::getFrame() const
	{
		return frame;
	}

	void Sprite3D::setFrameTime(const float new_frame_time)
	{
		frame_time = new_frame_time;
	}

	float Sprite3D::getFrameTime() const
	{
		return frame_time;
	}

	// 2D //

	Sprite2D::Sprite2D(Texture* texture)
		: frames(1, 1),
		frame(1, 1),
		frame_size(1.0f, 1.0f)
	{
		setTexture(texture);
	}

	Sprite2D::Sprite2D()
		: frames(1, 1),
		frame(1, 1),
		frame_size(1.0f, 1.0f)
	{
	}

	void Sprite2D::create()
	{
		quad = std::make_shared<VertexArray>();
		glm::vec2 size = texture->getSize();

		if (animated)
		{
			size /= frames;
			updateUVs();
		}
		else
		{
			std::shared_ptr<VertexBuffer> tex_coords(new VertexBuffer);
			tex_coords->add(glm::vec2(0.0f, 1.0f));
			tex_coords->add(glm::vec2(1.0f, 0.0f));
			tex_coords->add(glm::vec2(0.0f, 0.0f));
			tex_coords->add(glm::vec2(0.0f, 1.0f));
			tex_coords->add(glm::vec2(1.0f, 1.0f));
			tex_coords->add(glm::vec2(1.0f, 0.0f));

			quad->setBuffer("tex_coords", tex_coords);
		}

		std::shared_ptr<VertexBuffer> positions(new VertexBuffer);
		positions->add(glm::vec2(0.0f, size.y));
		positions->add(glm::vec2(size.x, 0.0f));
		positions->add(glm::vec2(0.0f, 0.0f));
		positions->add(glm::vec2(0.0f, size.y));
		positions->add(glm::vec2(size.x, size.y));
		positions->add(glm::vec2(size.x, 0.0f));
		quad->setBuffer("position", positions);
	}

	Texture* Sprite2D::getTexture() const
	{
		return texture;
	}

	void Sprite2D::setTexture(Texture* new_texture)
	{
		texture = new_texture;
		create();
	}

	void Sprite2D::draw(ShaderProgram& shader)
	{
		texture->bind();
		shader.setUniform("transform", getTransform());
		shader.draw(*quad);
		texture->unbind();
	}

	void Sprite2D::update(const float delta)
	{
		if (animated)
		{
			timer += delta;
			if (timer >= frame_time)
			{
				timer = 0.0f;
				if (++frame.x > frames.x)
				{
					frame.x = 1;
					if (++frame.y > frames.y)
						frame.y = 1;
				}

				updateUVs();
			}
		}
	}

	void Sprite2D::updateUVs()
	{
		std::shared_ptr<VertexBuffer> tex_coords(new VertexBuffer);

		frame_size.x = 1.0f / frames.x;
		frame_size.y = 1.0f / frames.y;

		glm::vec2 huv(frame_size.x * frame.x, frame_size.y * frame.y);
		glm::vec2 luv = huv - frame_size;

		tex_coords->add(glm::vec2(luv.x, huv.y));
		tex_coords->add(glm::vec2(huv.x, luv.y));
		tex_coords->add(glm::vec2(luv.x, luv.y));
		tex_coords->add(glm::vec2(luv.x, huv.y));
		tex_coords->add(glm::vec2(huv.x, huv.y));
		tex_coords->add(glm::vec2(huv.x, luv.y));

		quad->setBuffer("tex_coords", tex_coords);
	}

	void Sprite2D::setAnimated(const bool animate)
	{
		animated = animate;
	}

	bool Sprite2D::isAnimated() const
	{
		return animated;
	}

	void Sprite2D::setFrames(const glm::ivec2& new_frames)
	{
		frames = new_frames;
	}

	glm::ivec2 Sprite2D::getFrames() const
	{
		return frames;
	}

	void Sprite2D::setFrame(const glm::ivec2& new_frame)
	{
		frame = new_frame;
		updateUVs();
	}

	glm::ivec2 Sprite2D::getFrame() const
	{
		return frame;
	}

	void Sprite2D::setFrameTime(const float new_frame_time)
	{
		frame_time = new_frame_time;
	}

	float Sprite2D::getFrameTime() const
	{
		return frame_time;
	}
}