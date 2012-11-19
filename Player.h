#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"
#include "Animation.h"
#include "ResourceManager.h"


class EntityManager;

class Player : public Entity
{
	public:
		Player(sf::Vector2f pos, Map* map, EntityManager* entMgr);
		
		void input(sf::Event event);
		void update(int dt);
		
			
	private:
		Animation* m_anim;
		EntityManager* m_entMgr;
		
		int m_dir;
		int m_facing;
		
		void checkDirection();
		void kill();
		Map* m_map;
		
		int m_points;
};
