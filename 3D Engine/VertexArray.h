#pragma once

#include <memory>
#include "VertexBuffer.h"
#include "ApplicationException.h"
#include "Output.h"

namespace ENG
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void setBuffer(const std::string& attribute, const std::shared_ptr<VertexBuffer>& buffer);
		int getVertexCount();
		GLuint getID();
		std::vector<std::array<glm::vec3, 3>> getTriangles3D();

	private:
		GLuint id = 0;
		bool dirty = false;
		std::vector<std::shared_ptr<VertexBuffer>> buffers;
	};
}