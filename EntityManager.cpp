#include "EntityManager.h"

EntityManager::EntityManager(ResourceManager* resMgr, Map* map) : m_resMgr(resMgr), m_map(map)
{
	m_entities.push_back(new Player(sf::Vector2f(16, 16), m_map, m_resMgr));
}
