#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"
#include <vector>

class Square
{
	private:
		sf::Vector2i m_pos;	
		sf::Vector2i m_parentSquare;
		
	public:
		Square(sf::Vector2i pos) : m_pos(pos) { }
		Square(sf::Vector2i pos, sf::Vector2i parentSquare) 
				: m_pos(pos), m_parentSquare(parentSquare) { }
				
		sf::Vector2i getPos() { return m_pos; }
};

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
		
		int m_type;
		
		int m_dir;
		int m_facing;
		
		bool m_turned;
		
		sf::Clock m_turnTime;
		
		std::vector<Square> m_openList;
		sf::Vector2i m_dest;
		sf::Vector2i m_ntdest;
		
		bool m_onWay;
		bool m_gTnT;
};
