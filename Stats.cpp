#include "Stats.h"
#include <sstream>
#include "ResourceManager.h"
Stats* Stats::m_instance = NULL;

Stats::Stats() : m_points(0), m_lives(3)
{
	m_instance = this;
	
	m_pointsText.setPosition(0, 32*16);
	m_pointsText.setCharacterSize(16);
	m_pointsText.setColor(sf::Color::White);
	
	for(int i = 0; i < 3; i++)
	{
		m_lifeSpr[i].setTexture(*ResourceManager::get()->getPlayerTex());
		m_lifeSpr[i].setTextureRect(sf::IntRect(32, 0, 16, 16));
		m_lifeSpr[i].setPosition(i*16 + 200, 32*16);
	}
}

void Stats::render(sf::RenderWindow* win)
{
	std::stringstream s;
	s << "Points: " << m_points;
	
	m_pointsText.setString(s.str());
	
	win->draw(m_pointsText);
	for(int i = 0; i < m_lives; i++) win->draw(m_lifeSpr[i]);
}

Stats* Stats::get()
{
	if(m_instance == NULL) m_instance = new Stats();
	return m_instance;
}
