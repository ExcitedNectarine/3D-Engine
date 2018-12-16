#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ShaderProgram.h"

namespace ENG
{
	class Texture
	{
	public:
		Texture();
		Texture(const std::string& filename);
		void load(const std::string& filename);
		void bind();
		void unbind();
		glm::ivec2 getSize() const;

	private:
		GLuint id;
		glm::ivec2 size;
		int channels = 0;
	};
}