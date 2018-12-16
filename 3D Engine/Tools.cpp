#include "Tools.h"

namespace ENG
{
	namespace Tools
	{
		namespace Collision
		{
			AABB::AABB() {}
			AABB::AABB(const glm::vec3& position, const glm::vec3& size) : position(position), size(size) {}

			bool AABBTest(const AABB& a, const AABB& b)
			{
				return (a.position.x < b.position.x + b.size.x &&
					a.position.x + a.size.x > b.position.x &&
					a.position.y < b.position.y + b.size.y &&
					a.position.y + a.size.y > b.position.y &&
					a.position.z < b.position.z + b.size.z &&
					a.position.z + a.size.z > b.position.z);
			}
		}

		std::vector<std::string> splitString(const std::string& string, const char delimeter)
		{
			std::vector<std::string> items;
			std::stringstream ss(string);
			std::string item;

			while (std::getline(ss, item, delimeter))
				items.push_back(item);

			return items;
		}

		bool approximate(const float a, const float b, const float eps)
		{
			return std::abs(a - b) < eps;
		}
	}
}