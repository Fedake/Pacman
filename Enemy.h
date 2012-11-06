#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"
#include <vector>
#include "Animation.h"

class Square
{
	private:
		sf::Vector2f m_pos;	
		sf::Vector2f m_parentSquare;
		
	public:
		Square(sf::Vector2f pos) : m_pos(pos) { }
		Square(sf::Vector2f pos, sf::Vector2f parentSquare) 
				: m_pos(pos), m_parentSquare(parentSquare) { }
				
		sf::Vector2f getPos() { return m_pos; }
};

class Enemy : public Entity
{
	public:
		Enemy(sf::Vector2f pos, Map* map, int type);
		
		void checkDirection();
		
		void update(int dt);
		
		bool isInside(sf::FloatRect tile);
		
		bool isWayClear();
		
		bool aStar();
		
	private:
		Map* m_map;
		Animation* m_anim;
		
		int m_type;
		
		int m_dir;
		int m_facing;
		
		bool m_turned;
		
		sf::Clock m_turnTime;
		
		std::vector<Square> m_openList;
		
		bool m_onWay;
};
