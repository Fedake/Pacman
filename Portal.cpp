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
		if(m_player->getPos().x > m_pos.x + 8 && m_dir == 3)
		{
			int hDiff = m_player->getPos().y - exit->getPos().y;
			m_player->setPos(sf::Vector2f(exit->getPos().x, exit->getPos().y + hDiff));
		}
		if(m_player->getPos().x < m_pos.x - 8 && m_dir == 1)
		{
			int hDiff = m_player->getPos().y - exit->getPos().y;
			m_player->setPos(sf::Vector2f(exit->getPos().x, exit->getPos().y + hDiff));
		}
	}
}	
