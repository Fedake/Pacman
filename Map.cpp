#include "Map.h"
#include <fstream>
#include <iostream>

#include "Dot.h"
#include "Pellet.h"
#include "Portal.h"

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
	for(int w = 0; w < 31; w++)
	{
		file >> buffer;
		
		m_tiles[w][h] = new Tile(sf::Vector2f(w*16, h*16), buffer);
		m_solid[w][h] = buffer;
		if(buffer == 0)
		{
			m_entMgr->addEntity(new Dot(sf::Vector2f(w*16 + 7, h*16 + 7), m_entMgr->getPlayer())); 
		}
		if(buffer == 5)
		{
			m_entMgr->addEntity(new Pellet(sf::Vector2f(w*16 + 5, h*16 + 5), m_entMgr->getPlayer())); 
		}
		if(buffer == 6)
		{
			m_entMgr->addEntity(new Portal(sf::Vector2f(w*16, h*16), m_entMgr, 0, 1, 3)); 
		}
		if(buffer == 7)
		{
			m_entMgr->addEntity(new Portal(sf::Vector2f(w*16, h*16), m_entMgr, 1, 0, 1)); 
		}
	}
	
	
	
	return true;
}

void Map::render(sf::RenderWindow* win)
{
	for(int h = 0; h < 32; h++)
	for(int w = 0; w < 31; w++)
	{
		m_tiles[w][h]->render(win);
	}
}


