#include "stdafx.h"
#include "GameSettings.h"
#include "PlayState.h"
#include "Display.h"
#include "Util.h"
#include "BasicEnemy.h"
#include "BasicTower.h"
#include <SFML/Graphics.hpp>

void initTile(sf::RectangleShape& tile, const sf::Color &color) {
	tile.setSize(sf::Vector2f(GameSettings::BLOCK_SIZE, GameSettings::BLOCK_SIZE));

	tile.setOutlineThickness(2.f);
	tile.setOutlineColor(sf::Color::Black);
	tile.setFillColor(color);
}

PlayState::PlayState(Application& _app) : m_app (_app), m_enemiesDeleted(false), m_projectilesDeleted(false) {
	// Initialize terrain
	initTile(m_lowTerrain, sf::Color(0, 138, 255, 255));
	initTile(m_highTerrain, sf::Color(225, 225, 225, 255));
	initTile(m_entryPoint, sf::Color::Yellow);
	initTile(m_exitPoint, sf::Color::Cyan);

	// Initialize map
	if (m_map.loadMapFromFile("map002")) {
		Util::printMessage("Loaded map map002.");
	}

	// Initialize enemies
	m_enemies.push_back(new BasicEnemy(*this, m_map.getMapGraph()));

	// Initialize towers
	m_towers.push_back(new BasicTower(*this));
}


PlayState::~PlayState() {
}

void PlayState::input() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		m_app.popGameState();
	}

	// Towers input
	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->input();
	}
}

void PlayState::update(float _dt) {
	static sf::Clock timer;
	// Enemy spawn
	if (timer.getElapsedTime().asSeconds() >= GameSettings::ENEMY_SPAWN_PERIOD) {
		timer.restart();

		// Spawn new enemy
		m_enemies.push_back(new BasicEnemy(*this, m_map.getMapGraph()));
	}

	// Update enemies
	for (int i = 0; i < m_enemies.size(); ++i) {
		m_enemies[i]->update(_dt);
	}
	
	if (m_enemiesDeleted) {
		m_enemiesDeleted = false;
		m_enemies.erase(std::remove(m_enemies.begin(), m_enemies.end(), nullptr), m_enemies.end());
	}

	// Update towers
	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->update(_dt);
	}

	// Update projectiles
	for (int i = 0; i < m_projectiles.size(); ++i) {
		m_projectiles[i]->update(_dt);
	}
	if (m_projectilesDeleted) {
		m_projectilesDeleted = false;
		m_projectiles.erase(std::remove(m_projectiles.begin(), m_projectiles.end(), nullptr), m_projectiles.end());
	}
}

void drawTile(sf::RectangleShape& _tile, int _x, int _y) {
	_tile.setPosition(_x * GameSettings::BLOCK_SIZE, _y * GameSettings::BLOCK_SIZE);
	Display::draw(_tile);
}
void PlayState::draw() {
	// Draw map
	for (int x = 0; x < m_map.getMapWidth(); ++x) {
		for (int y = 0; y < m_map.getMapHeight(); ++y) {
			switch (m_map.getMapData(x, y)) {
			case Map::LOW_TERRAIN:
				drawTile(m_lowTerrain, x, y);
				break;
			case Map::HIGH_TERRAIN:
				drawTile(m_highTerrain, x, y);
				break;
			case Map::ENTRY_POINT:
				drawTile(m_entryPoint, x, y);
				break;
			case Map::EXIT_POINT:
				drawTile(m_exitPoint, x, y);
				break;
			}
		}
	}

	// Draw enemies
	for (int i = 0; i < m_enemies.size(); ++i) {
		m_enemies[i]->draw();
	}

	// Draw towers
	for (int i = 0; i < m_towers.size(); ++i) {
		m_towers[i]->draw();
	}

	// Draw projectiles
	for (int i = 0; i < m_projectiles.size(); ++i) {
		m_projectiles[i]->draw();
	}
}

void PlayState::notify(Enemy * _enemy) {
	for (int i = 0; i < m_enemies.size(); ++i) {
		if (m_enemies[i] == _enemy) {
			m_enemies[i] = nullptr;
			break;
		}
	}
	m_enemiesDeleted = true;
	delete _enemy;
}

void PlayState::notify(Projectile * _projectile) {
	for (int i = 0; i < m_projectiles.size(); ++i) {
		if (m_projectiles[i] == _projectile) {
			m_projectiles[i] = nullptr;
			break;
		}
	}
	m_projectilesDeleted = true;
	delete _projectile;
}

Map & const PlayState::getMap() {
	return m_map;
}

std::vector<Enemy*> PlayState::getEnemiesInRange(const sf::Vector2f & _center, const float & _radius) {
	std::vector<Enemy*> enemies;
	for (Enemy* e : m_enemies) {
		if (e) {
			if (Util::magnitude(e->getPosition() - _center) <= _radius) {
				enemies.push_back(e);
			}
		}
	}

	return enemies;
}

void PlayState::addProjectile(Projectile * _p) {
	m_projectiles.push_back(_p);
}
