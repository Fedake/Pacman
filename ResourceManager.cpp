#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	m_playerTex = new sf::Texture();
	m_playerTex->loadFromFile("player.png");
	
	m_entTex.push_back(new sf::Texture());
	m_entTex[0]->loadFromFile("dot.png");
}
