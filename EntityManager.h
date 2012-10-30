#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Map.h"
#include "Enemy.h"
#include "Stats.h"

class EntityManager
{
	public:
		EntityManager();
		
		Entity* getPlayer() { return m_entities[0]; }
		Entity* getEntity(int nr) { if (nr < m_entities.size()) return m_entities[nr]; }
		unsigned getSize(){return m_entities.size();}
		void addEntity(Entity* n){m_entities.push_back(n);}
		
		void render(sf::RenderWindow* win);
		void update(int dt);
		
	private:
		std::vector<Entity*> m_entities;
};
