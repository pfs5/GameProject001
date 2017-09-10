#pragma once

#include "GameState.h"
#include "Application.h"
#include "Map.h"
#include "Enemy.h"
#include "Tower.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>

class PlayState : public GameState {
	Application& m_app;

	// Map elements
	Map m_map;
	sf::RectangleShape m_lowTerrain;
	sf::RectangleShape m_highTerrain;
	sf::RectangleShape m_entryPoint;
	sf::RectangleShape m_exitPoint;

	// Game objects
	std::vector<Enemy*> m_enemies;
	bool m_enemiesDeleted;

	std::vector<Tower*> m_towers;
	std::vector<Projectile*> m_projectiles;
	bool m_projectilesDeleted;
public:
	PlayState(Application& _app);
	~PlayState();

	// Inherited via GameState
	virtual void input() override;
	virtual void update(float _dt) override;
	virtual void draw() override;

	void notify(Enemy *_enemy);
	void notify(Projectile *_projectile);

	Map& const getMap();

	std::vector<Enemy*> getEnemiesInRange(const sf::Vector2f& _center, const float& _radius);

	void addProjectile(Projectile *_p);
};

