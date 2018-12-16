#include "Level.h"

Level::Level(ENG::Application& app, ENG::BaseScene* scene)
	: ENG::BaseEntity(app, scene)
{
}

void Level::load(const std::string& filename)
{
	using namespace tinyxml2;

	// create a new XML document
	XMLDocument doc;
	if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) // if file failed to load, throw error
		throw ENG::ApplicationException("Level file '" + filename + "' could not be opened. " + doc.ErrorName());

	// get metadata about the tilemap, such as the width, height, and the name of the texture to use for tiles
	getTileMapData(doc.FirstChildElement("about"));

	// load the tileset
	texture = app.getResourceManager().getTexture(tileset);

	// Work out size of each tile
	int frame = 1;
	glm::vec2 frames(texture->getSize() / tilesize);
	glm::vec2 frame_size(1.0f / frames);
	glm::vec2 huv(frame_size.x * frame, frame_size.y * frame);
	glm::vec2 luv = huv - frame_size;

	std::shared_ptr<ENG::VertexBuffer> positions(new ENG::VertexBuffer);
	std::shared_ptr<ENG::VertexBuffer> tex_coords(new ENG::VertexBuffer);

	XMLElement* data = doc.FirstChildElement("data");
	XMLElement* layout = data->FirstChildElement("layout");

	// Get the layer and format it for easier parsing.
	std::string layout_text = layout->GetText();
	std::vector<std::string> layout_rows = formatData(layout_text);

	std::vector<std::vector<int>> layout_data;
	for (std::string& row : layout_rows)
	{
		std::vector<int> r;

		std::vector<std::string> numbers = ENG::Tools::splitString(row, '-');
		for (std::string& number : numbers)
			r.push_back(std::stoi(number));

		layout_data.push_back(r);
	}

	solid_grid.resize(length);
	for (std::vector<int>& row : solid_grid)
		row.resize(width);

	for (int z = 0; z < length; z++)
	{
		for (int x = 0; x < width; x++)
		{
			solid_grid[z][x] = 0;
			if (layout_data[z][x])
			{
				frame = 1;
				huv = frame_size * static_cast<float>(frame);
				luv = glm::abs(huv - frame_size);

				positions->add(glm::vec3(-1.0f, 1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
				positions->add(glm::vec3(1.0f, 1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
				positions->add(glm::vec3(-1.0f, 1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
				positions->add(glm::vec3(-1.0f, 1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
				positions->add(glm::vec3(1.0f, 1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
				positions->add(glm::vec3(1.0f, 1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));

				tex_coords->add(glm::vec2(luv.x, huv.y));
				tex_coords->add(glm::vec2(huv.x, luv.y));
				tex_coords->add(glm::vec2(luv.x, luv.y));
				tex_coords->add(glm::vec2(luv.x, huv.y));
				tex_coords->add(glm::vec2(huv.x, huv.y));
				tex_coords->add(glm::vec2(huv.x, luv.y));

				frame = 2;
				huv = frame_size * static_cast<float>(frame);
				luv = glm::abs(huv - frame_size);

				positions->add(glm::vec3(-1.0f, -1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
				positions->add(glm::vec3(1.0f, -1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
				positions->add(glm::vec3(-1.0f, -1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
				positions->add(glm::vec3(-1.0f, -1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
				positions->add(glm::vec3(1.0f, -1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
				positions->add(glm::vec3(1.0f, -1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));

				tex_coords->add(glm::vec2(luv.x, huv.y));
				tex_coords->add(glm::vec2(huv.x, luv.y));
				tex_coords->add(glm::vec2(luv.x, luv.y));
				tex_coords->add(glm::vec2(luv.x, huv.y));
				tex_coords->add(glm::vec2(huv.x, huv.y));
				tex_coords->add(glm::vec2(huv.x, luv.y));

				frame = layout_data[z][x] + 2;
				huv = frame_size * static_cast<float>(frame);
				luv = glm::abs(huv - frame_size);

				if (!layout_data[z - 1][x])
				{
					positions->add(glm::vec3(-1.0f, 1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(1.0f, -1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(-1.0f, -1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(-1.0f, 1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(1.0f, 1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(1.0f, -1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));

					tex_coords->add(glm::vec2(luv.x, huv.y));
					tex_coords->add(glm::vec2(huv.x, luv.y));
					tex_coords->add(glm::vec2(luv.x, luv.y));
					tex_coords->add(glm::vec2(luv.x, huv.y));
					tex_coords->add(glm::vec2(huv.x, huv.y));
					tex_coords->add(glm::vec2(huv.x, luv.y));
				}
				
				if (!layout_data[z][x - 1])
				{
					positions->add(glm::vec3(-1.0f, 1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(-1.0f, -1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(-1.0f, -1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(-1.0f, 1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(-1.0f, 1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(-1.0f, -1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));

					tex_coords->add(glm::vec2(luv.x, huv.y));
					tex_coords->add(glm::vec2(huv.x, luv.y));
					tex_coords->add(glm::vec2(luv.x, luv.y));
					tex_coords->add(glm::vec2(luv.x, huv.y));
					tex_coords->add(glm::vec2(huv.x, huv.y));
					tex_coords->add(glm::vec2(huv.x, luv.y));
				}
				
				if (!layout_data[z + 1][x])
				{
					positions->add(glm::vec3(-1.0f, 1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(1.0f, -1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(-1.0f, -1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(-1.0f, 1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(1.0f, 1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(1.0f, -1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));

					tex_coords->add(glm::vec2(luv.x, huv.y));
					tex_coords->add(glm::vec2(huv.x, luv.y));
					tex_coords->add(glm::vec2(luv.x, luv.y));
					tex_coords->add(glm::vec2(luv.x, huv.y));
					tex_coords->add(glm::vec2(huv.x, huv.y));
					tex_coords->add(glm::vec2(huv.x, luv.y));
				}

				
				if (!layout_data[z][x + 1])
				{
					positions->add(glm::vec3(1.0f, 1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(1.0f, -1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(1.0f, -1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(1.0f, 1.0f, -1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(1.0f, 1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));
					positions->add(glm::vec3(1.0f, -1.0f, 1.0f) + glm::vec3(2 * x, 0.0f, 2 * z));

					tex_coords->add(glm::vec2(luv.x, huv.y));
					tex_coords->add(glm::vec2(huv.x, luv.y));
					tex_coords->add(glm::vec2(luv.x, luv.y));
					tex_coords->add(glm::vec2(luv.x, huv.y));
					tex_coords->add(glm::vec2(huv.x, huv.y));
					tex_coords->add(glm::vec2(huv.x, luv.y));
				}
			}
			else
			{
				solid_grid[z][x] = 1;
			}
		}
	}

	vertices = std::make_shared<ENG::VertexArray>();
	vertices->setBuffer("position", positions);
	vertices->setBuffer("tex_coords", tex_coords);

	XMLElement* objects_element = data->FirstChildElement("objects");
	std::string object_text = objects_element->GetText();
	std::vector<std::string> object_rows = formatData(object_text);
	for (std::string& row : object_rows)
	{
		std::vector<int> object_row;
		std::vector<std::string> numbers = ENG::Tools::splitString(row, '-');
		for (std::string& number : numbers)
			object_row.push_back(std::stoi(number));
		objects.push_back(object_row);
	}
}

void Level::getTileMapData(tinyxml2::XMLElement* about)
{
	title = about->FirstChildElement("title")->GetText();
	tileset = about->FirstChildElement("tileset")->GetText();
	tilesize = std::stoi(about->FirstChildElement("tilesize")->GetText());
	width = std::stoi(about->FirstChildElement("width")->GetText());
	length = std::stoi(about->FirstChildElement("length")->GetText());

	OUTPUT("Title: " << title);
	OUTPUT("Tileset: " << tileset);
	OUTPUT("Tilesize: " << tilesize);
	OUTPUT("Width: " << width);
	OUTPUT("Length: " << length);
}

std::vector<ENG::Tools::Collision::AABB> Level::getObjects(const int object)
{
	// create a vector of rects for where objects should be
	std::vector<ENG::Tools::Collision::AABB> object_rects;
	for (int z = 0; z < length; z++) //  for each object tile in the map
		for (int x = 0; x < width; x++)
			if (objects[z][x] == object) // if the object type matches the object we want
				object_rects.emplace_back( // create a new rect based on where the object is, adding it to the vector
					glm::vec3(static_cast<float>(x * 2), 0.0f, static_cast<float>(z * 2)),
					glm::vec3(2.0f, 2.0f, 2.0f)
				);
	return object_rects; // return the object rects
}

std::vector<ENG::Tools::Collision::AABB> Level::getSurroundingSolids(const glm::vec3& pos)
{
	glm::vec3 position = glm::round(pos / 2.0f);
	std::vector<ENG::Tools::Collision::AABB> solids;
	ENG::Tools::Collision::AABB rect;
	rect.size = glm::vec3(2.0f, 2.0f, 2.0f);
	rect.position.y = 0.0f;

	glm::vec2 tiles[8] = {
		{ position.x - 1, position.z },
		{ position.x + 1, position.z },
		{ position.x, position.z - 1 },
		{ position.x, position.z + 1 },
		{ position.x - 1, position.z - 1},
		{ position.x + 1, position.z + 1},
		{ position.x - 1, position.z + 1},
		{ position.x + 1, position.z - 1}
	};

	for (const glm::vec2& tile : tiles) //  for each position
	{
		if ((tile.x > -1 && tile.x < length) && // if the position is in the map
			(tile.y > -1 && tile.y < width))
		{
			if (solid_grid[tile.y][tile.x]) // if the position's tile is a solid
			{
				rect.position.x = tile.x * 2;
				rect.position.z = tile.y * 2;
				solids.push_back(rect); // add it to the vector of rects
			}
		}
	}

	return solids; // return rects
}

std::vector<std::array<glm::vec3, 3>> Level::getTriangles3D()
{
	return vertices->getTriangles3D();
}

std::vector<std::string> Level::formatData(const std::string& data)
{
	// removes all useless text from each layer and puts it into a vector
	std::string data_copy = data;
	data_copy.erase(std::remove(data_copy.begin(), data_copy.end(), ' '), data_copy.end()); // erase all spaces
	std::vector<std::string> data_rows = ENG::Tools::splitString(data_copy, '\n');
	data_rows.erase(data_rows.begin());
	return data_rows;
}

void Level::draw(ENG::ShaderProgram& shader)
{
	texture->bind();
	shader.setUniform("transform", getTransform());
	shader.draw(*vertices);
	texture->unbind();
}