#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	m_playerTex = new sf::Texture();
	m_playerTex->loadFromFile("player.png");
}
