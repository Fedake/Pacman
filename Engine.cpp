#include "Engine.h"
Engine::Engine()
{
	m_win = new sf::RenderWindow(sf::VideoMode(32*16, 33*16, 32), "Pacman pre-alpha 0.0.1");
	m_win->setFramerateLimit(60);
	
	m_dbg = new Debug();
	
	m_entMgr = new EntityManager();
	
	m_map = new Map(m_entMgr);
	m_entMgr->addEntity(new Player(sf::Vector2f(16, 16), m_map, m_entMgr));
	
	srand(time(NULL));
	
	m_map->load("map.txt");
	
	m_entMgr->addEntity(new Enemy(sf::Vector2f(16, 16), m_map, 1));
}

Engine::~Engine()
{
	delete m_win;
}

void Engine::run()
{
	sf::Clock dt;
		
	while (m_win->isOpen())
	{
		handleEvents();
		update(dt.getElapsedTime());
		dt.restart();
		draw();
	}
}

void Engine::handleEvents()
{
	sf::Event event;
	
	while (m_win->pollEvent(event))
	{
		m_entMgr->getPlayer()->input(event);
		if (event.type == sf::Event::Closed)
		{
			m_win->close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::F1) m_dbg->toggle();
		}
	}
}

void Engine::update(sf::Time dt)
{
	m_entMgr->update(dt.asMicroseconds());
	
	m_dbg->update(m_entMgr->getPlayer()->getPos());
}

void Engine::draw()
{
	m_win->clear(sf::Color::Black);
	m_map->render(m_win);
	
	m_entMgr->render(m_win);
	
	Stats::get()->render(m_win);
	m_dbg->render(m_win);
	m_win->display();
}
