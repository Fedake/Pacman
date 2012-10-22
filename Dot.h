#pragma once
#include "Entity.h"

class Dot : public Entity
{
	private:
		Entity* m_player;
		
		
	public:
		Dot(sf::Vector2f pos, Entity* player);
		
		void update(int dt);
};

