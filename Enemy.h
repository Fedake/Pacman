#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"

class Enemy : public Entity
{
	public:
		Enemy(sf::Vector2f pos, Map* map, int type);
		
		void checkDirection();
		
		void update(int dt);
		
		bool isInside(sf::FloatRect tile);
		
	private:
		Map* m_map;		
		int m_type;
		
		int m_dir;
		int m_facing;
		
		bool m_curvnol;
};
