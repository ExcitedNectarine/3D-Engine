#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <chrono>
#include <glm/glm.hpp>

namespace ENG
{
	namespace Tools
	{
		namespace Collision
		{
			struct AABB
			{
				AABB();
				AABB(const glm::vec3& position, const glm::vec3& size);
				bool operator==(const AABB& b);

				glm::vec3 position;
				glm::vec3 size;
			};

			bool AABBTest(const AABB& a, const AABB& b);
		}

		std::vector<std::string> splitString(const std::string& string, const char delimeter);
		bool approximate(const float a, const float b, const float eps);
		int randomInt(const int from, const int to);
	}
}