#include "EntityManager.h"

EntityManager::EntityManager(ResourceManager* resMgr, Stats* stat) : m_resMgr(resMgr), m_stat(stat)
{
}

void EntityManager::update(int dt)
{
	for (unsigned int i = 0; i < m_entities.size(); ++i)
	{
		m_entities[i]->update(dt);
		
		if(m_entities[i]->shouldDie())
		{
			m_entities.erase(m_entities.begin() + i);
			m_stat->addPoints(10);
			i--;
		}
	}	
}


void EntityManager::render(sf::RenderWindow* win)
{
	for (int i = 0; i < m_entities.size(); ++i)
	{
		m_entities[i]->render(win);
	}
}
