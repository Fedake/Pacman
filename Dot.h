#pragma once
#include "Entity.h"
#include "ResourceManager.h"
#include "Stats.h"

class Dot : public Entity
{
	private:
		Entity* m_player;
		
	public:
		Dot(sf::Vector2f pos, Entity* player);
		
		void update(int dt);
};

