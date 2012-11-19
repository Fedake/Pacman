#include "Portal.h"

Portal::Portal(sf::Vector2f pos, EntityManager* entMgr, int type, int exit, int dir) 
	: Entity(pos, type, 80), m_entMgr(entMgr), m_exit(exit), m_dir(dir)
{
	m_player = m_entMgr->getPlayer();
	
	m_box.left = pos.x;
	m_box.top = pos.y;
	m_box.width = 16;
	m_box.height = 32;
}

void Portal::update(int dt)
{
	Entity* exit;
	for(unsigned i = 0; i < m_entMgr->getSize(); i++)
	{
		if(m_entMgr->getEntity(i)->getType() == 80)
		{
			if(m_entMgr->getEntity(i)->getId() == m_exit) exit = m_entMgr->getEntity(i);
		}
	}
	if(exit == NULL) return;
	
	if(m_player->getBox().intersects(m_box))
	{
		m_onPortal = true;
		int yDiff = m_player->getPos().y - m_pos.y;
		int xDiff = m_player->getPos().x - m_pos.x;
		
		if(m_dir == 1)
		{			
			m_playerGhost = m_player->getSprite();
			m_playerGhost.setPosition(exit->getPos() + sf::Vector2f(xDiff + 24, 8 + yDiff));
			
			if(m_player->getPos().x < m_pos.x - 8)
			{
				m_player->setPos(sf::Vector2f(exit->getPos().x - xDiff, exit->getPos().y + yDiff));
			}
		}
		else if(m_dir == 3)
		{
			m_playerGhost = m_player->getSprite();
			m_playerGhost.setPosition(exit->getPos() + sf::Vector2f(xDiff - 8, 8 + yDiff));
			
			if(m_player->getPos().x > m_pos.x + 8)
			{
				m_player->setPos(sf::Vector2f(exit->getPos().x - xDiff, exit->getPos().y + yDiff));
			}
		}
	}
	else m_onPortal = false;
}	

void Portal::render(sf::RenderWindow* win)
{
	win->draw(m_spr);
	if(m_onPortal) win->draw(m_playerGhost);
}

