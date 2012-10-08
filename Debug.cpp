#include "Debug.h"
#include <sstream>

Debug::Debug() : m_active(false)
{
	m_dbg.setCharacterSize(15);
	m_dbg.setPosition(sf::Vector2f(220, 20));
}

void Debug::update(sf::Vector2f pPos)
{
	std::stringstream d;
	
	d
	<< "x: " << pPos.x << "\n"
	<< "y: " << pPos.y;
	
	m_dbg.setString(d.str());
}
