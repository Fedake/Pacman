#include "Enemy.h"

#include <iostream>
#include <windows.h>
#include <conio.h>

Enemy::Enemy(sf::Vector2f pos, Map* map, int type) : Entity(pos, type, 93), m_map(map)
{
	m_anim = new Animation(ResourceManager::get()->getEnemyTex(type), 16, 16, 2, 100);
	m_anim->play();
	
	m_box.left = pos.x;
	m_box.top = pos.y;
	m_box.width = 15;
	m_box.height = 15;
	
	
	m_turned = false;
	
	m_turnTime.restart();
	
	m_dest.pos.x = 20;
	m_dest.pos.y = 1;
	
	m_onWay = false;
	
}

void Enemy::checkDirection()
{
//	if (sf::Vector2i(m_pos.x/16, m_pos.y/16) == m_dest)
//		m_onWay = false;
		
	if (!m_onWay) setNewDest();
	
	aStar();
	
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
	m_anim->setMode(m_dir);
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
	
	m_anim->update();
	m_spr = m_anim->getSprite();
	m_spr.setPosition(sf::Vector2f(m_box.left, m_box.top));
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
	std::cout << "newdest" << std::endl;
	// choose a random available destination	
	do
	{
		m_dest.pos.x = rand() % 32;
		m_dest.pos.y = rand() % 32;
	} while (m_map->isSolid(m_dest.pos.x, m_dest.pos.y));
	
	std::cout << "m_dest x: " << m_dest.pos.x << "  m_dest x: " << m_dest.pos.y << std::endl;
	m_onWay = true;
}

void Enemy::aStar()
{
	// get current position
	sf::Vector2i pos;
	pos.x = static_cast<int>((m_pos.x+8) / 16);
	pos.y = static_cast<int>((m_pos.y+8) / 16);
	
	m_openList.clear();
	m_closedList.clear();
	
	Node node;
	node.pos = pos;
	
	bool exit = false;
	while (!exit)
	{
		m_closedList.push_back(node);
		
		// get current position
		sf::Vector2i pos;
		pos.x = static_cast<int>((m_pos.x+8) / 16);
		pos.y = static_cast<int>((m_pos.y+8) / 16);
		
		if (isInside(sf::FloatRect(pos.x*16, pos.y*16, 16, 16)))
		{
			Node neighbour;
			neighbour.pos.x = node.pos.x + 1;
			neighbour.pos.y = node.pos.y;
			if (m_map->isSolid(neighbour.pos.x, neighbour.pos.y) == false && inClosedList(neighbour) == false)
				m_openList.push_back(neighbour);
			
			neighbour.pos.x = node.pos.x - 1;
			neighbour.pos.y = node.pos.y;
			if (m_map->isSolid(neighbour.pos.x, neighbour.pos.y) == false && inClosedList(neighbour) == false)
				m_openList.push_back(neighbour);
			
			neighbour.pos.x = node.pos.x;
			neighbour.pos.y = node.pos.y + 1;
			if (m_map->isSolid(neighbour.pos.x, neighbour.pos.y) == false && inClosedList(neighbour) == false)
				m_openList.push_back(neighbour);
			
			neighbour.pos.x = node.pos.x;
			neighbour.pos.y = node.pos.y - 1;
			if (m_map->isSolid(neighbour.pos.x, neighbour.pos.y) == false && inClosedList(neighbour) == false)
				m_openList.push_back(neighbour);
			
			for (int i = 0; i < m_openList.size(); ++i)
			{
				int G = 0;
				int H = 0;
			
				G = 1;
				H = abs(m_dest.pos.x - m_openList[i].pos.x) + abs(m_dest.pos.y - m_openList[i].pos.y);
				
				m_openList[i].cost = G + H;
			}
				
			int index = 0;
			for (int i = 0; i < m_openList.size(); ++i)
			{
				if (m_openList[i].cost < m_openList[index].cost)
				{
					if (!inClosedList(m_openList[i]))
						index = i;
				}
			}
			
			m_closedList.push_back(m_openList[index]);
			m_openList.clear();
			
			node = m_closedList[index];
			
			if (node.pos == m_dest.pos)
				exit = true;
			
			std::cout << "node: " << node.pos.x << " " << node.pos.y << std::endl;
			_getch();
		}
	}
}

bool Enemy::inClosedList(Node node)
{
	for (int i = 0; i < m_closedList.size(); ++i)
	{
		if (m_closedList[i].pos == node.pos) return true;
	}
	return false;
}
