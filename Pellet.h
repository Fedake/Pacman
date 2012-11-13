#pragma once
#include "Entity.h"
#include "ResourceManager.h"
#include "Stats.h"

class Pellet : public Entity
{
	private:
		Entity* m_player;
		
	public:
		Pellet(sf::Vector2f pos, Entity* player);
		
		void update(int dt);
};

