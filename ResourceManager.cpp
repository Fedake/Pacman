#include "ResourceManager.h"
ResourceManager* ResourceManager::m_instance = NULL;

ResourceManager::ResourceManager()
{
	m_playerTex = new sf::Texture();
	m_playerTex->loadFromFile("player.png");
	
	m_entTex.push_back(new sf::Texture());
	m_entTex[0]->loadFromFile("dot.png");
	
	m_entTex.push_back(new sf::Texture());
	m_entTex[1]->loadFromFile("sciana.png");
	
	m_entTex.push_back(new sf::Texture());
	m_entTex[2]->loadFromFile("pellet.png");
	
	m_enemyTex.push_back(new sf::Texture());
	m_enemyTex[0]->loadFromFile("ghost1.png");

	m_enemyTex.push_back(new sf::Texture());
	m_enemyTex[1]->loadFromFile("ghost2.png");
	
	m_enemyTex.push_back(new sf::Texture());
	m_enemyTex[2]->loadFromFile("ghost3.png");
	
	m_enemyTex.push_back(new sf::Texture());
	m_enemyTex[3]->loadFromFile("ghost4.png");
}

ResourceManager* ResourceManager::get()
{
	if(m_instance == NULL) m_instance = new ResourceManager();
	return m_instance;
}
