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
	
	m_dir = E_RIGHT;
	
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
	sf::Vector2i pos;
	pos.x = static_cast<int>(m_pos.x / 16);
	pos.y = static_cast<int>(m_pos.y / 16);
	
	
	// sprawdz czy mobek moze skrecic
	if (m_map->isCurve(pos.x, pos.y))
	{
		if (isInside(sf::FloatRect(pos.x*16, pos.y*16, 16, 16)))
		{
			switch (m_dir)
			{
				case E_LEFT:
					do
					{
						m_dir = rand() % 4;
					} while (m_dir == E_RIGHT);
					break;
					
				case E_RIGHT:
					do
					{
						m_dir = rand() % 4;
					} while (m_dir == E_LEFT);
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
				m_pos.x -= m_vel.x * (dt/1000000.f);
				m_box.left = m_pos.x;
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
				m_pos.y -= m_vel.y * (dt/1000000.f);
				m_box.top = m_pos.y;
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
		if (m_box.left >= tile.left)
		if (m_box.top >= tile.top)
		if ((m_box.left+m_box.width) <= (tile.left+tile.width))
		if ((m_box.top+m_box.height) <= (tile.left+tile.height))
		return true;
	}
	
	 return false;
}
