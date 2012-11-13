#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
	public:
		Animation(sf::Texture* tex, int width, int height, int frames, float frameTime);
		
		void update();
		
		void play(){m_play = true;}
		void stop(){m_play = false; m_sprite.setTextureRect(sf::IntRect(0, 0, m_width, m_height));}
		void setMode(int n){m_mode = n;}
		
		sf::Sprite getSprite(){return m_sprite;}
		
		
	private:
		sf::Sprite m_sprite;
		
		bool m_play;
		int m_mode;
		
		int m_width, m_height;
		
		int m_frame;
		int m_frames;
		
		float m_frameTime;
		
		sf::Clock m_timer;
		
};
