#pragma once
#include <SFML/Graphics.hpp>

class Stats
{
	public:		
		void render(sf::RenderWindow* win);
		
		void addPoints(int x){m_points += x;}
		void addLives(int x){m_lives += x;}
		int getPoints(){return m_points;}
		int getLives(){return m_lives;}	
		
		static Stats* get();
		
	private:
		Stats();
		static Stats* m_instance;
		
		sf::Sprite m_lifeSpr[3];
		sf::Text m_pointsText;
		sf::Text m_livesText;
		
		int m_points;
		int m_lives;	
		
};
