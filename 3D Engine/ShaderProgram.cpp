#include "ShaderProgram.h"

namespace ENG
{
	ShaderProgram::ShaderProgram(const std::string& vert, const std::string& frag)
	{
		create(vert, frag);
	}

	ShaderProgram::ShaderProgram()
	{
	}

	void ShaderProgram::create(const std::string& vert, const std::string& frag)
	{
		GLint success = 0;

		// Compile vertex shader.
		std::string vert_text = readShader(vert);
		const GLchar* vert_source = vert_text.c_str();
		GLuint vert_id = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vert_id, 1, &vert_source, NULL);
		glCompileShader(vert_id);
		compileErrorCheck(vert_id);

		// Compile fragment shader.
		std::string frag_text = readShader(frag);
		const GLchar* frag_source = frag_text.c_str();
		GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(frag_id, 1, &frag_source, NULL);
		glCompileShader(frag_id);
		compileErrorCheck(frag_id);

		// Create a shader program from the two shaders.
		id = glCreateProgram();
		glAttachShader(id, vert_id);
		glAttachShader(id, frag_id);
		glBindAttribLocation(id, 0, "position");
		glBindAttribLocation(id, 1, "tex_coords");
		glBindAttribLocation(id, 2, "normals");
		glLinkProgram(id);
		linkErrorCheck();

		// Get rid of old shader info, no longer needed.
		glDetachShader(id, vert_id);
		glDeleteShader(vert_id);
		glDetachShader(id, vert_id);
		glDeleteShader(vert_id);
	}

	void ShaderProgram::draw(VertexArray& vertices)
	{
		glUseProgram(id);
		glBindVertexArray(vertices.getID());

		glDrawArrays(GL_TRIANGLES, 0, vertices.getVertexCount());

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(const std::string& uniform, const glm::mat4& value)
	{
		GLint uniform_id = glGetUniformLocation(id, uniform.c_str());
		if (uniform_id == -1)
			throw ApplicationException("Uniform '" + uniform + "' not found.");

		glUseProgram(id);
		glUniformMatrix4fv(uniform_id, 1, GL_FALSE, &value[0][0]);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(const std::string& uniform, const glm::vec3& value)
	{
		GLint uniform_id = glGetUniformLocation(id, uniform.c_str());
		if (uniform_id == -1)
			throw ApplicationException("Uniform '" + uniform + "' not found.");

		glUseProgram(id);
		glUniform3fv(uniform_id, 1, &value[0]);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(const std::string& uniform, float value)
	{
		GLint uniform_id = glGetUniformLocation(id, uniform.c_str());
		if (uniform_id == -1)
			throw ApplicationException("Uniform '" + uniform + "' not found.");

		glUseProgram(id);
		glUniform1f(uniform_id, value);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(const std::string& uniform, int value)
	{
		GLint uniform_id = glGetUniformLocation(id, uniform.c_str());
		if (uniform_id == -1)
			throw ApplicationException("Uniform '" + uniform + "' not found.");

		glUseProgram(id);
		glUniform1i(uniform_id, value);
		glUseProgram(0);
	}

	GLuint ShaderProgram::getID()
	{
		return id;
	}

	std::string ShaderProgram::readShader(const std::string& filename)
	{
		std::ifstream file(filename.c_str());
		if (!file.is_open())
			throw ApplicationException("Unable to open shader file '" + filename + "'.");

		std::string contents;
		std::string line;

		while (!file.eof())
		{
			std::getline(file, line);
			contents.append(line + '\n');
		}

		return contents;
	}

	void ShaderProgram::compileErrorCheck(const GLuint shader_id)
	{
		GLint success = 0;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			GLint max = 0;
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max);
			std::vector<GLchar> log(max);
			glGetShaderInfoLog(shader_id, max, &max, &log[0]);

			throw ApplicationException(&log[0]);
		}
	}

	void ShaderProgram::linkErrorCheck()
	{
		GLint success = 0;
		glGetProgramiv(id, GL_LINK_STATUS, &success);

		if (!success)
		{
			GLint max = 0;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &max);
			std::vector<GLchar> log(max);
			glGetProgramInfoLog(id, max, &max, &log[0]);

			throw ApplicationException(&log[0]);
		}
	}
}