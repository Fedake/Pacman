#pragma once
#include <SFML/Graphics.hpp>

class Stats
{
	public:
		Stats();
		
		void render(sf::RenderWindow* win);
		
		
		
		
		void addPoints(int x){m_points += x;}
		int getPoints(){return m_points;}	
		
		
	private:
		sf::Text m_pointsText;
		
		
		int m_points;
		int m_lives;	
		
};
