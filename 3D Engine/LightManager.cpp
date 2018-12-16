#include "LightManager.h"

namespace ENG
{
	LightManager::LightManager(const glm::vec3& ambient)
		: ambient(ambient)
	{
	}

	glm::vec3 LightManager::getAmbient()
	{
		return ambient;
	}

	void LightManager::setAmbient(const glm::vec3& ambient)
	{
		this->ambient = ambient;
	}

	uint16_t LightManager::add(const glm::vec3& position, const glm::vec3& colour, const float radius)
	{
		if (light_sources.size() + 1 > MAX_LIGHT_SOURCES) return 0;
		light_sources.emplace_back(++ids, position, colour, radius);
		return ids;
	}

	void LightManager::remove(const uint16_t id)
	{
		auto it = std::find(light_sources.begin(), light_sources.end(), id);
		if (it == light_sources.end()) return;
		light_sources.erase(it);
	}

	void LightManager::setPosition(const uint16_t id, const glm::vec3& position)
	{
		auto it = std::find(light_sources.begin(), light_sources.end(), id);
		if (it == light_sources.end()) return;
		it->position = position;
	}

	void LightManager::setColour(const uint16_t id, const glm::vec3& colour)
	{
		auto it = std::find(light_sources.begin(), light_sources.end(), id);
		if (it == light_sources.end()) return;
		it->colour = colour;
	}

	void LightManager::setRadius(const uint16_t id, const float radius)
	{
		auto it = std::find(light_sources.begin(), light_sources.end(), id);
		if (it == light_sources.end()) return;
		it->radius = radius;
	}

	std::vector<LightSource> LightManager::getLightSources()
	{
		return light_sources;
	}
}