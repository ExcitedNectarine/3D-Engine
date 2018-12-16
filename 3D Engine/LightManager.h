#pragma once

#include <vector>
#include <glm/glm.hpp>

#define MAX_LIGHT_SOURCES 128

namespace ENG
{
	struct LightSource
	{
		LightSource(const uint16_t uid, const glm::vec3& position, const glm::vec3& colour, const float radius)
			: uid(uid), position(position), colour(colour), radius(radius) {}

		bool operator==(const uint16_t rhs) {
			return uid == rhs;
		}

		uint16_t uid;
		glm::vec3 position;
		glm::vec3 colour;
		float radius;
	};

	class LightManager
	{
	public:
		LightManager(const glm::vec3& ambient);
		glm::vec3 getAmbient();
		void setAmbient(const glm::vec3& ambient);
		uint16_t add(const glm::vec3& position, const glm::vec3& colour, const float radius);
		void remove(const uint16_t id);
		void setPosition(const uint16_t id, const glm::vec3& position);
		void setColour(const uint16_t id, const glm::vec3& colour);
		void setRadius(const uint16_t id, const float radius);
		std::vector<LightSource> getLightSources();

	private:
		uint16_t ids = 0;
		std::vector<LightSource> light_sources;
		glm::vec3 ambient;
	};
}