#include "Tile.h"
#include "ResourceManager.h"


Tile::Tile(sf::Vector2f pos, int type)
{
	m_spr.setPosition(pos);
	
	switch (type)
	{
		case 1:
			m_spr.setTexture(*ResourceManager::get()->getEntityTex(1)); break;
		default:
			break;
	}
}
