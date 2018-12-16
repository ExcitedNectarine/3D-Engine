#include "VertexArray.h"

namespace ENG
{
	VertexArray::VertexArray()
	{
		buffers.resize(10);
		glGenVertexArrays(1, &id);

		if (!id)
			throw ApplicationException("Failed to generate vertex array.");
	}

	void VertexArray::setBuffer(const std::string& attribute, const std::shared_ptr<VertexBuffer>& buffer)
	{
		if (attribute == "position")
			buffers.at(0) = buffer;
		else if (attribute == "tex_coords")
			buffers.at(1) = buffer;
		else if (attribute == "normals")
			buffers.at(2) = buffer;
		else
			throw ApplicationException("Unknown vertex buffer assigned.");

		dirty = true;
	}

	int VertexArray::getVertexCount()
	{
		if (!buffers.at(0))
			throw ApplicationException("No position buffer assigned.");

		return buffers.at(0)->getDataSize() / buffers.at(0)->getComponents();
	}

	GLuint VertexArray::getID()
	{
		if (dirty)
		{
			glBindVertexArray(id);

			for (std::size_t i = 0; i < buffers.size(); i++)
			{
				if (buffers.at(i))
				{
					glBindBuffer(GL_ARRAY_BUFFER, buffers.at(i)->getID());
					glVertexAttribPointer(
						i,
						buffers.at(i)->getComponents(),
						GL_FLOAT,
						GL_FALSE,
						buffers.at(i)->getComponents() * sizeof(GLfloat),
						(void*)0
					);
					glEnableVertexAttribArray(i);
				}
			}

			glBindVertexArray(0);

			dirty = false;
		}

		return id;
	}

	std::vector<std::array<glm::vec3, 3>> VertexArray::getTriangles3D()
	{
		if (!buffers.at(0))
			throw ApplicationException("No position buffer assigned.");

		return buffers.at(0)->getTriangles3D();
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}
}