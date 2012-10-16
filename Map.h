#ifndef MAP_H
#define MAP_H

#include "Tile.h"

class EntityManager;


class Map
{
	public:
		Map(std::string name, EntityManager* entMgr);
		~Map();
		
		bool load(std::string name);
		
		
		void render(sf::RenderWindow* win);
		
		bool isSolid(int x, int y){return m_solid[x][y];}
		
	private:
		EntityManager* m_entMgr;
		
		Tile* m_tiles[32][32];
		bool m_solid[32][32];
};

#endif
