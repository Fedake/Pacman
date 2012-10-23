#include "Stats.h"
#include <sstream>
Stats::Stats() : m_points(0), m_lives(999)
{
	m_pointsText.setPosition(0, 32*16);
	m_pointsText.setCharacterSize(16);
	m_pointsText.setColor(sf::Color::Black);
}

void Stats::render(sf::RenderWindow* win)
{
	std::stringstream s;
	s << "Points: " << m_points;
	
	m_pointsText.setString(s.str());
	
	win->draw(m_pointsText);
}
