#include "Tile.h"



Tile::Tile(sf::Vector2f pos, int type)
{
	m_shape.setSize(sf::Vector2f(16, 16));
	m_shape.setPosition(pos);
	
	switch (type)
	{
		case 1:
			m_shape.setFillColor(sf::Color::Red); break;
		default:
			m_shape.setFillColor(sf::Color::Black); break;
	}
}
