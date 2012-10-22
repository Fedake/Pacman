#include "Map.h"
#include <fstream>
#include "Dot.h"
#include "EntityManager.h"
#include "Player.h"
#include "Entity.h"

Map::Map(EntityManager* entMgr) : m_entMgr(entMgr)
{
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
		m_solid[w][h] = buffer == 0 ? false : true;
		//if(buffer == 0)
		//{
		//	m_entMgr->addEntity(new Dot(sf::Vector2f(w*32, h*32), player)); 
		//}
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


