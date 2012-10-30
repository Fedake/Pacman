#include "EntityManager.h"

EntityManager::EntityManager()
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
