#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace ENG
{
	Texture::Texture() {}

	Texture::Texture(const std::string& filename)
	{
		load(filename);
	}

	void Texture::load(const std::string& filename)
	{
		// Flips file data so it is compatible with the way OpenGL interprets the data.
		stbi_set_flip_vertically_on_load(1);

		unsigned char* data = stbi_load(filename.c_str(), &size.x, &size.y, &channels, 4);
		if (!data)
			throw std::exception();

		glGenTextures(1, &id);

		if (!id)
			throw std::exception();

		glBindTexture(GL_TEXTURE_2D, id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		free(data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		unbind();
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glm::ivec2 Texture::getSize() const
	{
		return size;
	}
}