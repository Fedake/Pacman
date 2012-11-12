#include "Player.h"
#include <iostream>
#include "EntityManager.h"

using namespace std;

Player::Player(sf::Vector2f pos, Map* map, EntityManager* entMgr) : Entity(pos, 0, 0), m_map(map), m_entMgr(entMgr)
{
	m_anim = new Animation(ResourceManager::get()->getPlayerTex(), 16, 16, 3, 100);
	m_box.left = m_pos.x;
	m_box.top = m_pos.y;
	m_box.width = 15;
	m_box.height = 15;
}

void Player::input(sf::Event ev)
{
	if(ev.type == sf::Event::KeyPressed)
	{
		if(ev.key.code == sf::Keyboard::W) 
		{
			m_dir = E_UP;
		}
		else if(ev.key.code == sf::Keyboard::S) 
		{
			m_dir = E_DOWN;
		}
		else if(ev.key.code == sf::Keyboard::A) 
		{
			m_dir = E_LEFT;
		}
		else if(ev.key.code == sf::Keyboard::D)
		{
			m_dir = E_RIGHT;
		}
	}
}

void Player::checkDirection()
{
	sf::Vector2i tPos;
	tPos.x = static_cast<int>((m_pos.x+8) / 16);
	tPos.y = static_cast<int>((m_pos.y+8) / 16);
	
	int cc = 0;
	int lc = 0;
	
	for (int h = tPos.y - 1; h <= tPos.y + 1; ++h)
	for (int w = tPos.x - 1; w <= tPos.x + 1; ++w)
	{
		if (m_dir == E_UP)
		{
			sf::FloatRect box;
			box.left = m_pos.x;
			box.top = m_pos.y-15;
			box.width = 15;
			box.height = 15;
			
			++lc;
			if (m_map->isSolid(w, h) && box.intersects(sf::FloatRect(w*16, h*16, 16, 16))) ++cc;
			
			if (lc == 9 && cc == 0)
			{
				m_vel.x = 0;
				m_vel.y = -50;
				m_facing = E_UP;
			}
		}
		
		if (m_dir == E_DOWN)
		{
			sf::FloatRect box;
			box.left = m_pos.x;
			box.top = m_pos.y+15;
			box.width = 15;
			box.height = 15;
			
			++lc;
			if (m_map->isSolid(w, h) && box.intersects(sf::FloatRect(w*16, h*16, 16, 16))) ++cc;
			
			if (lc == 9 && cc == 0)
			{
				m_vel.x = 0;
				m_vel.y = 50;
				m_facing = E_DOWN;
			}
		}
		
		if (m_dir == E_LEFT)
		{
			sf::FloatRect box;
			box.left = m_pos.x-15;
			box.top = m_pos.y;
			box.width = 15;
			box.height = 15;
			
			++lc;
			if (m_map->isSolid(w, h) && box.intersects(sf::FloatRect(w*16, h*16, 16, 16))) ++cc;
			
			if (lc == 9 && cc == 0)
			{
				m_vel.x = -50;
				m_vel.y = 0;
				m_facing = E_LEFT;
			}
		}
		
		if (m_dir == E_RIGHT)
		{
			sf::FloatRect box;
			box.left = m_pos.x+15;
			box.top = m_pos.y;
			box.width = 15;
			box.height = 15;
			
			++lc;
			if (m_map->isSolid(w, h) && box.intersects(sf::FloatRect(w*16, h*16, 16, 16))) ++cc;
			
			if (lc == 9 && cc == 0)
			{
				m_vel.x = 50;
				m_vel.y = 0;
				m_facing = E_RIGHT;
			}
		}
	}
}

void Player::update(int dt)
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
				std::cout << "kolX" << std::endl;
				switch (m_facing)
				{
					case E_LEFT:
						m_pos.x = w*16+16;
						m_box.left = m_pos.x;
						break;
					case E_RIGHT:
						m_pos.x = w*16-m_box.width;
						m_box.left = m_pos.x;
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
				std::cout << "kolY" << std::endl;
				switch (m_facing)
				{
					case E_UP:
						m_pos.y = h*16+16;
						m_box.top = m_pos.y;
						break;
					case E_DOWN:
						m_pos.y = h*16-m_box.height;
						m_box.top = m_pos.y;
						break;
				}
				m_vel.y = 0;
			}
		}
	}
	
	if(m_vel.x == 0 && m_vel.y == 0) m_anim->stop();
	else m_anim->play();
	m_anim->update();
	m_spr = m_anim->getSprite();
	m_spr.setOrigin(8, 8);
	m_spr.setRotation((m_facing+1)*90);
	m_spr.setPosition(m_pos + sf::Vector2f(8, 8));
	
	for(unsigned i = 0; i < m_entMgr->getSize(); i++)
	{
		if(m_entMgr->getEntity(i)->getType() == 93)
		{
			if(m_entMgr->getEntity(i)->getBox().intersects(m_box))
			{
				kill();
			}
		}
	}
}

void Player::kill()
{
	Stats::get()->addLives(-1);
	
	m_pos = sf::Vector2f(16, 16);
	m_box.left = m_pos.x;
	m_box.top = m_pos.y;
	m_box.width = 15;
	m_box.height = 15;
}

