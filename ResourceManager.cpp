#include "ResourceManager.h"
ResourceManager* ResourceManager::m_instance = NULL;

ResourceManager::ResourceManager()
{
	m_playerTex = new sf::Texture();
	m_playerTex->loadFromFile("player.png");
	
	m_entTex.push_back(new sf::Texture());
	m_entTex[0]->loadFromFile("dot.png");
}

ResourceManager* ResourceManager::get()
{
	if(m_instance == NULL) m_instance = new ResourceManager();
	return m_instance;
}
