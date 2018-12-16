#pragma once

#include <string>
#include <map>
#include <memory>
#include <experimental/filesystem>
#include "Texture.h"
#include "Tools.h"
#include "ApplicationException.h"

namespace ENG
{
	class ResourceManager
	{
	public:
		void loadAll(const std::string& texture_directory);

		template <typename ResourceType>
		std::map<std::string, ResourceType> loadAllResource(const std::string& resource_directory)
		{
			namespace fs = std::experimental::filesystem; // shorten namespace

			std::map<std::string, ResourceType> resources; // create map for resource
			if (fs::exists(resource_directory)) // if the resource directory exists
			{
				for (auto& path : fs::directory_iterator(resource_directory)) // get the name of every file in the directory
				{
					std::string path_text = path.path().string();
					std::string file = Tools::splitString(path_text, '\\').back();

					OUTPUT("Loading file '" << file << "'.");

					ResourceType resource; // create a new resource
					resource.load(path_text); // load the file

					resources[file] = resource; // copy it to the map
				}
			}

			return resources; // return the map of resource
		}

		Texture* getTexture(const std::string& filename);

	private:
		std::map<std::string, Texture> textures;
	};
}