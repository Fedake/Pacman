#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"

class Enemy : public Entity
{
	public:
		Enemy(sf::Vector2f pos, Map* map);
		//~Enemy();
		
		//void update(int dt);
		
	private:
		Map* m_map;
};
