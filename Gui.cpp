#include "Gui.h"

Gui::Gui()
{
	m_pText.setColor(sf::Color::White);
	m_pText.setString("Points: 0");
}

void Gui::render(sf::RenderWindow* win)
{
	win->draw(m_pText);
}
