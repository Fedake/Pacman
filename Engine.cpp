#include "Engine.h"

Engine::Engine()
{
	m_win = new sf::RenderWindow(sf::VideoMode(32*16, 32*16, 32), "Pacman");
	m_win->setFramerateLimit(60);
	
	m_resMgr = new ResourceManager();
	
	m_map = new Map("map.txt", m_entMgr);
	
	m_entMgr = new EntityManager(m_resMgr, m_map);
	
	m_entMgr->addEnemy(16, 16, 1);
	
	m_dbg = new Debug();
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
	m_entMgr->getPlayer()->update(dt.asMicroseconds());
	
	m_dbg->update(m_entMgr->getPlayer()->getPos());
}

void Engine::draw()
{
	m_win->clear(sf::Color::White);
	m_map->render(m_win);
	
	m_entMgr->render(m_win);
	
	m_dbg->render(m_win);
	m_win->display();
}
