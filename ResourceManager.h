#pragma once

#include <SFML/Graphics.hpp>

class ResourceManager
{
	public:
		ResourceManager();
		sf::Texture* getPlayerTex(){return m_playerTex;}
		
		
		
		
	private:
		sf::Texture* m_playerTex;
		
		
		
};
