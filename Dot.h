#pragma once
#include "Entity.h"

class Player;

class Dot : public Entity
{
	private:
		Player* m_player;
		
		
	public:
		Dot(sf::Vector2f pos, Player* player);
		
		void update(int dt);	
};

