#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"
#include "Animation.h"
#include "ResourceManager.h"

class Player : public Entity
{
	public:
		Player(sf::Vector2f pos, Map* map, ResourceManager* resMgr);
		
		void input(sf::Event event);
		void update(int dt);
			
	private:
		Animation* m_anim;
		
		int m_dir;
		int m_facing;
		
		void checkDirection();
		Map* m_map;
		
		int m_points;
};
