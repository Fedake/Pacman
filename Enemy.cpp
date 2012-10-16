#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, Map* map, int type) : Entity(pos, 0, type)
{
	m_box.left = pos.x;
	m_box.top = pos.y;
	m_box.width = 15;
	m_box.height = 15;
	
	switch (m_type)
	{
		case 1:
		default:
			m_shape.setPosition(sf::Vector2f(m_box.left, m_box.top));
			m_shape.setSize(sf::Vector2f(m_box.width, m_box.height));
			m_shape.setFillColor(sf::Color::Green);
	}
}

void Enemy::update(int dt)
{
	
}
