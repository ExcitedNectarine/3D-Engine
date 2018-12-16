#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_transform_2d.hpp>
#include "ShaderProgram.h"

namespace ENG
{
	class Transformable3D
	{
	public:
		Transformable3D();

		glm::vec3 getPosition() const;
		void setPosition(const glm::vec3& new_position);
		void moveBy(const glm::vec3& move_by);

		glm::vec3 getRotation() const;
		void setRotation(const glm::vec3& new_rotation);
		void rotateBy(const glm::vec3& rotate_by);

		glm::vec3 getScale() const;
		void setScale(const glm::vec3& new_scale);
		void scaleBy(const glm::vec3& scale_by);

		glm::vec3 getForward() const;
		glm::vec3 getRight() const;
		glm::mat4 getTransform() const;

	protected:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};

	class Transformable2D
	{
	public:
		Transformable2D();

		glm::vec2 getPosition() const;
		void setPosition(const glm::vec2& new_position);
		void moveBy(const glm::vec2& move_by);

		float getRotation() const;
		void setRotation(const float new_rotation);
		void rotateBy(const float rotate_by);

		glm::vec2 getScale() const;
		void setScale(const glm::vec2& new_scale);
		void scaleBy(const glm::vec2& scale_by);

		glm::vec2 getOrigin() const;
		void setOrigin(const glm::vec2& new_origin);

		glm::mat4 getTransform() const;

	protected:
		glm::vec2 position;
		glm::vec2 scale;
		glm::vec2 origin;
		float rotation = 0.0f;
	};
}