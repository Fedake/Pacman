#pragma once
#include <SFML/Graphics.hpp>

class Debug
{
	public:
		Debug();
		
		void update(int dt, sf::Vector2f pos);
		void toggle(){m_active = !m_active;}
		
		void render(sf::RenderWindow* win){if(m_active) win->draw(m_dbg);}
		
	private:
		sf::Text m_dbg;
		
		bool m_active;
		
		
};
