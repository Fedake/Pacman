#pragma once
#include "Entity.h"
#include "ResourceManager.h"

class Dot : public Entity
{
	private:
		Entity* m_player;
		
		
	public:
		Dot(sf::Vector2f pos, ResourceManager* resMgr, Entity* player);
		
		void update(int dt);
};

