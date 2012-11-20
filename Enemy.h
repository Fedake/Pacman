#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"
#include <vector>
#include "Animation.h"

struct Node
{
	sf::Vector2i pos;
	int cost;
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
		
		bool inClosedList(Node node);
		
	private:
		Map* m_map;
		Animation* m_anim;
		
		int m_type;
		
		int m_dir;
		int m_facing;
		
		bool m_turned;
		
		sf::Clock m_turnTime;
		
		std::vector<Node> m_openList;
		std::vector<Node> m_closedList;
		Node m_dest;
		Node m_ntdest;
		
		std::vector<Node> m_path;
		
		sf::Vector2i m_lastPos;
		
		bool m_onWay;
		bool m_gTnT;
};
