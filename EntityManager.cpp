#include "EntityManager.h"

EntityManager::EntityManager(ResourceManager* resMgr, Map* map) : m_resMgr(resMgr), m_map(map)
{
	m_entities.push_back(new Player(sf::Vector2f(16, 16), m_map, m_resMgr));
}

void EntityManager::render(sf::RenderWindow* win)
{
	for (int i = 0; i < m_entities.size(); ++i)
	{
		m_entities[i]->render(win);
	}
}

void EntityManager::update(int dt)
{
	for (int i = 0; i < m_entities.size(); ++i)
	{
		m_entities[i]->update(dt);
	}
}
