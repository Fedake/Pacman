#pragma once

#include <SFML\Graphics.hpp>
#include <ctime>

#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Debug.h"
#include "EntityManager.h"

class Engine
{
	public:
		Engine();
		~Engine();
		
		void run();
		
	private:
		sf::RenderWindow* m_win;
		
		ResourceManager* m_resMgr;
		
		Map* m_map;
		Debug* m_dbg;
		
		EntityManager* m_entMgr;
		
		void handleEvents();
		void draw();
		void update(sf::Time dt);
};
