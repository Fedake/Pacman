#include "Tile.h"



Tile::Tile(sf::Vector2f pos, int type)
{
	m_shape.setSize(sf::Vector2f(16, 16));
	m_shape.setPosition(pos);
	m_shape.setFillColor(type == 0 ? sf::Color::Black : sf::Color::Red);
}
