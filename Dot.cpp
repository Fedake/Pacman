#include "Dot.h"

Dot::Dot(sf::Vector2f pos, Entity* player) : Entity(pos, 0, 0), m_player(player)
{
	m_spr.setTexture(*ResourceManager::get()->getEntityTex(0));
	m_spr.setPosition(pos);
	
	m_box.left = pos.x;
	m_box.top = pos.y;
	m_box.width = 2;
	m_box.height = 2;
}
		
void Dot::update(int dt)
{
	if(m_player->getBox().contains(m_pos))
	{
		Stats::get()->addPoints(10);
		m_die = true;
	}
}	
