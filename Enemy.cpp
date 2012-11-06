#include "Enemy.h"

#include <iostream>
#include <windows.h>

Enemy::Enemy(sf::Vector2f pos, Map* map, int type) : Entity(pos, 0, type), m_map(map)
{
	m_anim = new Animation(ResourceManager::get()->getPlayerTex(), 16, 16, 3, 100);
	m_anim->play();
	
	m_box.left = pos.x;
	m_box.top = pos.y;
	m_box.width = 15;
	m_box.height = 15;
	
	m_vel.y = 0;
	m_vel.x = 30;
	
	m_turned = false;
	
	m_turnTime.restart();
	
	m_dir = E_RIGHT;
	
}

void Enemy::checkDirection()
{
	if (m_onWay);
	
	
	sf::Vector2i pos;
	pos.x = static_cast<int>((m_pos.x+8) / 16);
	pos.y = static_cast<int>((m_pos.y+8) / 16);
	// sprawdz czy mobek moze skrecic
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
	
	// ustaw predkosc
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

bool Enemy::aStar()
{
	// choose a random available destination
	sf::Vector2i dest;
	
	do
	{
		dest.x = rand() % 32;
		dest.y = rand() % 32;
	} while (m_map->isSolid(dest.x, dest.y));
	
	sf::Vector2i pos;
	pos.x = static_cast<int>((m_pos.x+8) / 16);
	pos.y = static_cast<int>((m_pos.y+8) / 16);
	
	// add current square
	m_openList.push_back(Square(sf::Vector2f(pos.x, pos.y)));
	
	// add all reachable squares and set current square as parent
	for (int h = pos.y-1; h < pos.y+1; ++h)
	for (int w = pos.x-1; w < pos.x+1; ++w)
	{
		if (w == pos.x && h == pos.y) continue;
		
		m_openList.push_back(Square(sf::Vector2f(w, h), sf::Vector2f(pos.x, pos.y)));
	}
	
	for (int i = 0; i < m_openList.size(); ++i)
	{
		float Gx = m_openList[i].getPos().x;
	}
}
