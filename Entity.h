#pragma once

#include <SFML/Graphics.hpp>

enum direction { E_UP, E_RIGHT, E_DOWN, E_LEFT };

class Entity
{
	public:		
		Entity(sf::Vector2f pos, int id, int type);
				
		virtual void input(sf::Event event) {}
		virtual void update(int dt) = 0;
		void render(sf::RenderWindow* win){win->draw(m_spr); win->draw(m_shape);}
		
		sf::Vector2f getPos(){return m_pos;}
		sf::Vector2f getVel(){return m_vel;}
		sf::FloatRect getBox(){return m_box;}
		
		int getId(){return m_id;}
		int getType(){return m_type;}
		
		bool shouldDie(){return m_die;}
		
		void setPos(sf::Vector2f n){m_pos = n;}

	protected:
		int m_id;	
			
		sf::Vector2f m_pos;
		sf::Vector2f m_vel;
		
		sf::FloatRect m_box;
		
		sf::Sprite m_spr;
		sf::RectangleShape m_shape;
		
		int m_type;
		
		bool m_die;		
};
