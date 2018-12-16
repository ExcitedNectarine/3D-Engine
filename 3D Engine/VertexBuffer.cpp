#include "VertexBuffer.h"

namespace ENG
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &id);

		if (!id)
			throw ApplicationException("Failed to generate vertex buffer.");
	}

	void VertexBuffer::add(const glm::vec2& value)
	{
		if (components != 2 && components != 0)
			throw ApplicationException("Incorrect components assigned to vertex buffer.");

		data.push_back(value.x);
		data.push_back(value.y);

		components = 2;
		dirty = true;
	}

	void VertexBuffer::add(const glm::vec3& value)
	{
		if (components != 3 && components != 0)
			throw ApplicationException("Incorrect components assigned to vertex buffer.");

		data.push_back(value.x);
		data.push_back(value.y);
		data.push_back(value.z);

		components = 3;
		dirty = true;
	}

	void VertexBuffer::add(const glm::vec4& value)
	{
		if (components != 4 && components != 0)
			throw ApplicationException("Incorrect components assigned to vertex buffer.");

		data.push_back(value.x);
		data.push_back(value.y);
		data.push_back(value.z);
		data.push_back(value.w);

		components = 4;
		dirty = true;
	}

	GLuint VertexBuffer::getID()
	{
		if (dirty)
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data.at(0), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			dirty = false;
		}

		return id;
	}

	int VertexBuffer::getComponents()
	{
		return components;
	}

	int VertexBuffer::getDataSize()
	{
		return data.size();
	}

	void VertexBuffer::clear()
	{
		data.clear();
		components = 0;
		dirty = true;
	}

	std::vector<std::array<glm::vec3, 3>> VertexBuffer::getTriangles3D()
	{
		std::vector<std::array<glm::vec3, 3>> triangles;
		for (int i = 0; i < getDataSize(); i += 9)
		{
			std::array<glm::vec3, 3> tri;
			tri[0] = glm::vec3(data[i], data[i + 1], data[i + 2]);
			tri[1] = glm::vec3(data[i + 3], data[i + 4], data[i + 5]);
			tri[2] = glm::vec3(data[i + 6], data[i + 7], data[i + 8]);
			triangles.push_back(tri);
		}

		return triangles;
	}
}