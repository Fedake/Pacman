#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "ResourceManager.h"

class Player;
class Entity;
class EntityManager;

class Map
{
	public:
		Map(ResourceManager* resMgr, EntityManager* entMgr);
		~Map();
		
		bool load(std::string name);
		
		void render(sf::RenderWindow* win);
		
		bool isSolid(int x, int y) { return m_solid[x][y] == 1 ? true : false; }
		bool isCurve(int x, int y) { return m_solid[x][y] == 2 ? true : false; }
		
	private:
		ResourceManager* m_resMgr;
		EntityManager* m_entMgr;
		
		Tile* m_tiles[32][32];
		int m_solid[32][32];
};

#endif
