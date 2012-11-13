#include "Pellet.h"

Pellet::Pellet(sf::Vector2f pos, Entity* player) : Entity(pos, 0, 0), m_player(player)
{
	m_spr.setTexture(*ResourceManager::get()->getEntityTex(2));
	m_spr.setPosition(pos);
	
	m_box.left = pos.x;
	m_box.top = pos.y;
	m_box.width = 2;
	m_box.height = 2;
}
		
void Pellet::update(int dt)
{
	if(m_player->getBox().contains(m_pos))
	{
		Stats::get()->addPoints(50);
		m_die = true;
	}
}	
