#include "ResourceManager.h"

namespace ENG
{
	void ResourceManager::loadAll(const std::string& texture_directory)
	{
		textures = loadAllResource<Texture>(texture_directory);
	}

	Texture* ResourceManager::getTexture(const std::string& filename)
	{
		auto it = textures.find(filename);
		if (it == textures.end())
			throw ApplicationException("Texture '" + filename + "' could not be found.");
		return &it->second;
	}
}