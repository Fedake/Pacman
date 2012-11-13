#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"
#include <vector>
#include "Animation.h"

class Enemy : public Entity
{
	public:
		Enemy(sf::Vector2f pos, Map* map, int type);
		
		void checkDirection();
		
		void update(int dt);
		
		bool isInside(sf::FloatRect tile);
		
		bool isWayClear();
		
		void setNewDest();
		
		void aStar();
		
	private:
		Map* m_map;
		Animation* m_anim;
		
		int m_type;
		
		int m_dir;
		int m_facing;
		
		bool m_turned;
		
		sf::Clock m_turnTime;
		
		std::vector<sf::Vector2i> m_openList;
		sf::Vector2i m_dest;
		sf::Vector2i m_ntdest;
		
		bool m_onWay;
		bool m_gTnT;
};
