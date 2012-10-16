#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"

class Enemy : public Entity
{
	public:
		Enemy(sf::Vector2f pos, Map* map, int type);
		
		void update(int dt);
		
	private:
		Map* m_map;
		
		int m_type;
};
