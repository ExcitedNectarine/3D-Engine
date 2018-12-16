#pragma once

#include <tinyxml2.h>
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Application.h"
#include "EntityManager.h"

class Level : public ENG::BaseEntity
{
public:
	Level(ENG::Application& app, ENG::BaseScene* scene);
	void load(const std::string& filename);
	void getTileMapData(tinyxml2::XMLElement* about);
	std::vector<std::string> formatData(const std::string& data);
	std::vector<ENG::Tools::Collision::AABB> getObjects(const int object);
	std::vector<ENG::Tools::Collision::AABB> getSurroundingSolids(const glm::vec3& pos);
	std::vector<std::array<glm::vec3, 3>> getTriangles3D();
	void draw(ENG::ShaderProgram& shader);

private:
	std::shared_ptr<ENG::VertexArray> vertices;
	ENG::Texture* texture;
	std::string title;
	std::string tileset;
	int tilesize;
	int width;
	int length;
	std::vector<std::vector<int>> objects;
	std::vector<std::vector<int>> solid_grid;
};