#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
	public:
		Tile(sf::Vector2f pos, int type);
		
		void render(sf::RenderWindow* win){win->draw(m_shape);}
	private:
		sf::RectangleShape m_shape;
};

#endif
