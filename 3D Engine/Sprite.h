#pragma once

#include "Transformable.h"
#include "Drawable.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Output.h"

namespace ENG
{
	class Sprite3D : public Transformable3D, public Drawable
	{
	public:
		Sprite3D(Texture* texture);
		Sprite3D();
		void create();
		Texture* getTexture() const;
		void setTexture(Texture* texture);
		void draw(ShaderProgram& shader);
		bool isBillboard() const;
		void setBillboard(const float billboard, Transformable3D* camera);
		void update(const float delta);
		void updateUVs();
		void setAnimated(const bool animate);
		bool isAnimated() const;
		void setFrames(const glm::ivec2& new_frames);
		glm::ivec2 getFrames() const;
		void setFrame(const glm::ivec2& new_frame);
		glm::ivec2 getFrame() const;
		void setFrameTime(const float new_frame_time);
		float getFrameTime() const;

	private:
		Texture* texture;
		std::shared_ptr<VertexArray> quad;
		bool billboard = false;
		Transformable3D* camera = nullptr;

		bool animated = false;
		glm::ivec2 frame;
		glm::ivec2 frames;
		glm::vec2 frame_size;
		float frame_time = 0.0f;
		float timer = 0.0f;
	};

	// 2D //

	class Sprite2D : public Transformable2D, public Drawable
	{
	public:
		Sprite2D(Texture* texture);
		Sprite2D();
		void create();
		Texture* getTexture() const;
		void setTexture(Texture* texture);
		void draw(ShaderProgram& shader);
		void update(const float delta);
		void updateUVs();
		void setAnimated(const bool animate);
		bool isAnimated() const;
		void setFrames(const glm::ivec2& new_frames);
		glm::ivec2 getFrames() const;
		void setFrame(const glm::ivec2& new_frame);
		glm::ivec2 getFrame() const;
		void setFrameTime(const float new_frame_time);
		float getFrameTime() const;

	private:
		Texture* texture;
		std::shared_ptr<VertexArray> quad;
		
		bool animated = false;
		glm::ivec2 frame;
		glm::ivec2 frames;
		glm::vec2 frame_size;
		float frame_time = 0.0f;
		float timer = 0.0f;
	};
}