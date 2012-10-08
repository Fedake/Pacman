#include <SFML/Graphics.hpp>

class Gui
{
	public:
		Gui();
		void update();
		void render(sf::RenderWindow* win);
		
	private:
		sf::Text m_pText;
		
		int m_points;
};
