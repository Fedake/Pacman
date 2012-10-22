#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Map.h"
#include "Enemy.h"

class EntityManager
{
	public:
		EntityManager(ResourceManager* resMgr, Map* map);
		
		Entity* getPlayer() { return m_entities[0]; }
		Entity* getEntity(int nr) { if (nr < m_entities.size()) return m_entities[nr]; }
		
		void addEnemy(int x, int y, int type) { m_entities.push_back(new Enemy(sf::Vector2f(x, y), m_map, type)); }
		void addEntity(Entity* n){m_entities.push_back(n);}
		
		void render(sf::RenderWindow* win);
		
	private:
		std::vector<Entity*> m_entities;
		
		ResourceManager* m_resMgr;
		Map* m_map;
};
