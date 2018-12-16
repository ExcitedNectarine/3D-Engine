#include "Transformable.h"

namespace ENG
{
	Transformable3D::Transformable3D()
		: position(0.0f, 0.0f, 0.0f),
		rotation(0.0f, 0.0f, 0.0f),
		scale(1.0f, 1.0f, 1.0f)
	{
	}

	glm::vec3 Transformable3D::getPosition() const
	{
		return position;
	}

	void Transformable3D::setPosition(const glm::vec3& new_position)
	{
		position = new_position;
	}

	void Transformable3D::moveBy(const glm::vec3& move_by)
	{
		position += move_by;
	}

	glm::vec3 Transformable3D::getRotation() const
	{
		return rotation;
	}

	void Transformable3D::setRotation(const glm::vec3& new_rotation)
	{
		rotation = new_rotation;
	}

	void Transformable3D::rotateBy(const glm::vec3& rotate_by)
	{
		rotation += rotate_by;
	}

	glm::vec3 Transformable3D::getScale() const
	{
		return scale;
	}

	void Transformable3D::setScale(const glm::vec3& new_scale)
	{
		scale = new_scale;
	}

	void Transformable3D::scaleBy(const glm::vec3& scale_by)
	{
		scale += scale_by;
	}

	glm::vec3 Transformable3D::getForward() const
	{
		glm::mat4 transform = getTransform();
		return glm::vec3(transform[2].x, transform[2].y, transform[2].z);
	}

	glm::vec3 Transformable3D::getRight() const
	{
		glm::mat4 transform = getTransform();
		return glm::vec3(transform[0].x, transform[0].y, transform[0].z);
	}

	glm::mat4 Transformable3D::getTransform() const
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
		transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		return glm::scale(transform, scale);
	}

	// 2D //

	Transformable2D::Transformable2D()
		: position(0.0f, 0.0f),
		scale(1.0f, 1.0f),
		origin(0.0f, 0.0f)
	{
	}

	glm::vec2 Transformable2D::getPosition() const
	{
		return position;
	}

	void Transformable2D::setPosition(const glm::vec2& new_position)
	{
		position = new_position;
	}

	void Transformable2D::moveBy(const glm::vec2& move_by)
	{
		position += move_by;
	}

	float Transformable2D::getRotation() const
	{
		return rotation;
	}

	void Transformable2D::setRotation(const float new_rotation)
	{
		rotation = new_rotation;
	}

	void Transformable2D::rotateBy(const float rotate_by)
	{
		rotation += rotate_by;
	}

	glm::vec2 Transformable2D::getScale() const
	{
		return scale;
	}

	void Transformable2D::setScale(const glm::vec2& new_scale)
	{
		scale = new_scale;
	}

	void Transformable2D::scaleBy(const glm::vec2& scale_by)
	{
		scale += scale_by;
	}

	glm::vec2 Transformable2D::getOrigin() const
	{
		return origin;
	}

	void Transformable2D::setOrigin(const glm::vec2& new_origin)
	{
		origin = new_origin;
	}

	glm::mat4 Transformable2D::getTransform() const
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position - origin, 0.0f));

		transform = glm::translate(transform, glm::vec3(-origin, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::translate(transform, glm::vec3(origin, 0.0f));

		return glm::scale(transform, glm::vec3(scale, 1.0f));
	}
}