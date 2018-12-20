#include "Tools.h"

namespace ENG
{
	namespace Tools
	{
		namespace Collision
		{
			AABB::AABB() {}
			AABB::AABB(const glm::vec3& position, const glm::vec3& size) : position(position), size(size) {}

			bool AABB::operator==(const AABB& b)
			{
				return position == b.position && size == b.size;
			}

			bool AABBTest(const AABB& a, const AABB& b)
			{
				glm::vec3 a_pos = a.position - (a.size / 2.0f);
				glm::vec3 b_pos = b.position - (b.size / 2.0f);

				return (a_pos.x < b_pos.x + b.size.x &&
					a_pos.x + a.size.x > b_pos.x &&
					a_pos.y < b_pos.y + b.size.y &&
					a_pos.y + a.size.y > b_pos.y &&
					a_pos.z < b_pos.z + b.size.z &&
					a_pos.z + a.size.z > b_pos.z);

				/*
				return (a.position.x < b.position.x + b.size.x &&
						a.position.x + a.size.x > b.position.x &&
						a.position.y < b.position.y + b.size.y &&
						a.position.y + a.size.y > b.position.y &&
						a.position.z < b.position.z + b.size.z &&
						a.position.z + a.size.z > b.position.z); */
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

		int randomInt(const int from, const int to)
		{
			static std::default_random_engine engine(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
			std::uniform_int_distribution<int> dist(from, to);
			return dist(engine);
		}
	}
}