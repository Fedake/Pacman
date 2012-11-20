#include "Animation.h"



Animation::Animation(sf::Texture* tex, int width, int height, int frames, float frameTime) 
					: m_width(width), m_height(height), m_frames(frames), m_frameTime(frameTime), m_mode(0), m_frame(0), m_play(false)
{
	m_sprite.setTexture(*tex);	
	m_sprite.setTextureRect(sf::IntRect(m_frame*m_width, m_mode*m_height, m_width, m_height));	
	
	m_timer.restart();
}

void Animation::update()
{
	if(m_timer.getElapsedTime().asMilliseconds() > m_frameTime && m_play)
	{
		m_timer.restart();
		m_frame++;
		if(m_frame >= m_frames) m_frame = 0;
		m_sprite.setTextureRect(sf::IntRect(m_frame*m_width, m_mode*m_height, m_width, m_height));
	}
	
}
