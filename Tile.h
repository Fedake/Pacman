#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
	public:
		Tile(sf::Vector2f pos, int type);
		
		void render(sf::RenderWindow* win){win->draw(m_spr);}
	private:
		sf::Sprite m_spr;
};

#endif
