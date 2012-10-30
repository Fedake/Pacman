#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class ResourceManager
{
	public:
		sf::Texture* getPlayerTex(){return m_playerTex;}
		sf::Texture* getEntityTex(int n){return m_entTex[n];}
		
		static ResourceManager* get();
		
		
		
	private:
		ResourceManager();
		static ResourceManager* m_instance;
		
		sf::Texture* m_playerTex;
		std::vector<sf::Texture*> m_entTex;
		
		
		
};
