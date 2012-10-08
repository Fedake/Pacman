#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, Map* map) : Entity(pos, 0, 0)
{
	m_box.left = pos.x;
	m_box.top = pos.y;
	m_box.width = 15;
	m_box.height = 15;
}


