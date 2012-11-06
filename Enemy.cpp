#include "Enemy.h"

#include <iostream>
#include <windows.h>

Enemy::Enemy(sf::Vector2f pos, Map* map, int type) : Entity(pos, 0, type), m_map(map)
{
	m_box.left = pos.x;
	m_box.top = pos.y;
	m_box.width = 15;
	m_box.height = 15;
	
	m_vel.y = 0;
	m_vel.x = 30;
	
	m_turned = false;
	
	m_turnTime.restart();
	
	m_onWay = false;
	
	switch (m_type)
	{
		case 1:
		default:
			m_shape.setPosition(sf::Vector2f(m_box.left, m_box.top));
			m_shape.setSize(sf::Vector2f(m_box.width, m_box.height));
			m_shape.setFillColor(sf::Color::Green);
	}
}

void Enemy::checkDirection()
{
	if (m_pos == m_dest)
		m_onWay = false;
		
	if (!m_onWay) setNewDest();
	
	aStar();
	
	/*
	sf::Vector2i pos;
	pos.x = static_cast<int>((m_pos.x+8) / 16);
	pos.y = static_cast<int>((m_pos.y+8) / 16);
	// check if enemy can turn
	if (m_map->isTurn(pos.x, pos.y) && m_turnTime.getElapsedTime().asMilliseconds() > 500)
	{
		if (isInside(sf::FloatRect(pos.x*16, pos.y*16, 17, 17)))
		{
			bool wayClear = false;
			
			switch (m_dir)
			{
				case E_LEFT:
					do
					{
						m_dir = rand() % 4;
						if (isWayClear()) wayClear = true;
						else wayClear = false;
					} while (m_dir == E_RIGHT || !wayClear);
					m_turnTime.restart();
					break;
					
				case E_RIGHT:
					do
					{
						m_dir = rand() % 4;
						if (isWayClear()) wayClear = true;
						else wayClear = false;
					} while (m_dir == E_LEFT || !wayClear);
					m_turnTime.restart();
					break;
						
				case E_DOWN:
					do
					{
						m_dir = rand() % 4;
						if (isWayClear()) wayClear = true;
						else wayClear = false;
					} while (m_dir == E_UP || !wayClear);
					m_turnTime.restart();
					break;
					
				case E_UP:
					do
					{
						m_dir = rand() % 4;
						if (isWayClear()) wayClear = true;
						else wayClear = false;
					} while (m_dir == E_DOWN || !wayClear);
					m_turnTime.restart();
					break;
						
				default:
					break;
			}
		}
	}
	*/
	
	// set velocity
	switch (m_dir)
	{
		case E_LEFT:
			m_vel.x = -30;
			m_vel.y = 0;
			break;
		case E_RIGHT:
			m_vel.x = 30;
			m_vel.y = 0;
			break;
		case E_UP:
			m_vel.x = 0;
			m_vel.y = -30;
			break;
		case E_DOWN:
			m_vel.x = 0;
			m_vel.y = 30;
			break;
		default:
			break;
	}
}

void Enemy::update(int dt)
{
	checkDirection();
	
	m_pos.x += m_vel.x * (dt/1000000.f);
	m_box.left = m_pos.x;
	for (int h = 0; h < 32; ++h)
	for (int w = 0; w < 32; ++w)
	{
		if (m_map->isSolid(w, h))
		{
			if (m_box.intersects(sf::FloatRect(w*16, h*16, 16, 16)))
			{
				switch (m_dir)
				{
					case E_LEFT:
						m_pos.x = w*16+16;
						m_box.left = w*16+16;
						break;
					case E_RIGHT:
						m_pos.x = w*16-m_box.width;
						m_box.left = w*16-m_box.width;
						break;
				}
				m_vel.x = 0;
			}
		}
	}
	
	m_pos.y += m_vel.y * (dt/1000000.f);
	m_box.top = m_pos.y;
	for (int h = 0; h < 32; ++h)
	for (int w = 0; w < 32; ++w)
	{
		if (m_map->isSolid(w, h))
		{
			if (m_box.intersects(sf::FloatRect(w*16, h*16, 16, 16)))
			{
				switch (m_dir)
				{
					case E_UP:
						m_pos.y = h*16+16;
						m_box.top = h*16+16;
						break;
					case E_DOWN:
						m_pos.y = h*16-m_box.height;
						m_box.top = h*16-m_box.height;
						break;
				}
				m_vel.y = 0;
			}
		}
	}
	
	m_shape.setPosition(sf::Vector2f(m_box.left, m_box.top));
}

bool Enemy::isInside(sf::FloatRect tile)
{
	// tutaj Lesiek przypomjal co mam robic
	if (m_box.intersects(tile))
	{
		if ((m_box.left >= tile.left) &&
		   (m_box.top >= tile.top) &&
		   ((m_box.left+m_box.width) <= (tile.left+tile.width)) &&
		   ((m_box.top+m_box.height) <= (tile.left+tile.height)))
		return true;
	}
	
	 return false;
}

bool Enemy::isWayClear()
{
	sf::Vector2i pos;
	pos.x = static_cast<int>((m_pos.x+8) / 16);
	pos.y = static_cast<int>((m_pos.y+8) / 16);
	
	switch (m_dir)
	{
		case E_LEFT:
			if (m_map->isSolid(pos.x-1, pos.y)) return false;
			break;
		case E_RIGHT:
			if (m_map->isSolid(pos.x+1, pos.y)) return false;
			break;
		case E_UP:
			if (m_map->isSolid(pos.x, pos.y-1)) return false;
			break;
		case E_DOWN:
			if (m_map->isSolid(pos.x, pos.y+1)) return false;
			break;
	}
	
	return true;
}

void Enemy::setNewDest()
{
	// choose a random available destination
	do
	{
		m_dest.x = rand() % 32;
		m_dest.y = rand() % 32;
	} while (m_map->isSolid(m_dest.x, m_dest.y));
	
	m_onWay = true;
}

void Enemy::aStar()
{
	// get current position
	sf::Vector2i pos;
	pos.x = static_cast<int>((m_pos.x+8) / 16);
	pos.y = static_cast<int>((m_pos.y+8) / 16);
	
	// add current square
	//m_openList.push_back(Square(pos));
	
	if (isInside(sf::FloatRect(pos.x, pos.y, 16, 16)));
	{
		// add all reachable squares and set current square as parent
		if (!m_map->isSolid(pos.x-1, pos.y))
			m_openList.push_back(Square(sf::Vector2i(pos.x-1, pos.y), pos));
			
		if (!m_map->isSolid(pos.x+1, pos.y))	
		m_openList.push_back(Square(sf::Vector2i(pos.x+1, pos.y), pos));
		
		if (!m_map->isSolid(pos.x, pos.y-1))
		m_openList.push_back(Square(sf::Vector2i(pos.x, pos.y-1), pos));
		
		if (!m_map->isSolid(pos.x, pos.y+1))
		m_openList.push_back(Square(sf::Vector2i(pos.x, pos.y+1), pos));
		
		sf::Vector2i nextSquare;
		
		int prevCost = 9999;
		
		for (int i = 0; i < m_openList.size(); ++i)
		{
			// cost to move from current to the next square
			int G = 10;
			
			// cost to move from current square to final destination
			int H = abs(pos.x - m_dest.x) * 10 + abs(pos.y - m_dest.y) * 10;
			
			int cost = G + H;
			
			if (cost < prevCost)
			{
				nextSquare = m_openList[i].getPos();
				m_ntdest.x = nextSquare.x;
				m_ntdest.y = nextSquare.x;
				
				prevCost = cost;
			}
		}
		if (pos.x - nextSquare.x < 0)
			m_dir = E_RIGHT;
		else if (pos.x - nextSquare.x > 0)
			m_dir = E_LEFT;
		if (pos.y - nextSquare.y < 0)
			m_dir = E_DOWN;
		else if (pos.y - nextSquare.y > 0)
			m_dir = E_UP;
			
		m_gTnT = true;
		
		std::cout << "x: " << pos.x - nextSquare.x << "  y: " << pos.y - nextSquare.y;
		std::cout << "  m_dir: " << m_dir << std::endl;
			
		m_openList.clear();
	}
}
