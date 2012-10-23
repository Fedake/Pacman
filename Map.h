#ifndef MAP_H
#define MAP_H

#include "Tile.h"

class Map
{
	public:
		Map(std::string name);
		~Map();
		
		bool load(std::string name);
		
		
		void render(sf::RenderWindow* win);
		
		bool isSolid(int x, int y) { return m_solid[x][y] == 1 ? true : false; }
		bool isCurve(int x, int y) { return m_solid[x][y] == 2 ? true : false; }
		
	private:
		Tile* m_tiles[32][32];
		int m_solid[32][32];
};

#endif
