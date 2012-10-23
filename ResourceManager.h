#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class ResourceManager
{
	public:
		ResourceManager();
		sf::Texture* getPlayerTex(){return m_playerTex;}
		sf::Texture* getEntityTex(int n){return m_entTex[n];}
		
		
		
	private:
		sf::Texture* m_playerTex;
		
		std::vector<sf::Texture*> m_entTex;
		
		
		
};
