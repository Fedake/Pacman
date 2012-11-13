#pragma once
#include "Entity.h"
#include "EntityManager.h"

class Portal : public Entity
{
	private:
		EntityManager* m_entMgr;
		Entity* m_player;
		int m_dir;
		int m_exit;
		
	public:
		Portal(sf::Vector2f pos, EntityManager* entMgr, int type, int exit, int dir);
		void update(int dt);
};

