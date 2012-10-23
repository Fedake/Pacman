#include "Map.h"
#include <fstream>
#include <iostream>

Map::Map(std::string name)
{
	load(name);
}

Map::~Map()
{
	
}

bool Map::load(std::string name)
{
	std::ifstream file;
	file.open("map.txt");
	
	int buffer;
	for(int h = 0; h < 32; h++)
	for(int w = 0; w < 32; w++)
	{
		file >> buffer;
		
		m_tiles[w][h] = new Tile(sf::Vector2f(w*16, h*16), buffer);
		m_solid[w][h] = buffer;
	}
	
	return true;
}

void Map::render(sf::RenderWindow* win)
{
	for(int h = 0; h < 32; h++)
	for(int w = 0; w < 32; w++)
	{
		m_tiles[w][h]->render(win);
	}
}


