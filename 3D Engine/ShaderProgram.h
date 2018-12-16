#pragma once

#include <string>
#include <fstream>
#include "VertexArray.h"
#include "Output.h"

namespace ENG
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vert, const std::string& frag);
		ShaderProgram();
		void create(const std::string& vert, const std::string& frag);
		void draw(VertexArray& vertices);
		void setUniform(const std::string& uniform, const glm::mat4& value);
		void setUniform(const std::string& uniform, const glm::vec3& value);
		void setUniform(const std::string& uniform, float value);
		void setUniform(const std::string& uniform, int value);
		GLuint getID();
		std::string readShader(const std::string& filename);
		void compileErrorCheck(const GLuint shader_id);
		void linkErrorCheck();

	private:
		GLuint id;
	};
}