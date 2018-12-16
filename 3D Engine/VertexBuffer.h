#pragma once

#include <array>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ApplicationException.h"

namespace ENG
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		void add(const glm::vec2& value);
		void add(const glm::vec3& value);
		void add(const glm::vec4& value);
		GLuint getID();
		int getComponents();
		int getDataSize();
		void clear();
		std::vector<std::array<glm::vec3, 3>> getTriangles3D();

	private:
		GLuint id = 0;
		bool dirty = false;
		int components = 0;
		std::vector<GLfloat> data;
	};
}