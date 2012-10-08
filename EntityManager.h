#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Map.h"

class EntityManager
{
	public:
		EntityManager(ResourceManager* resMgr, Map* map);
		
		Entity* getPlayer() { return m_entities[0]; }
		Entity* getEntity(int nr) { if (nr < m_entities.size()) return m_entities[nr]; }
		
	private:
		std::vector<Entity*> m_entities;
		
		ResourceManager* m_resMgr;
		Map* m_map;
};
