#include "stdafx.h"
#include "BasicTower.h"
#include "GameSettings.h"
#include "Display.h"
#include "PlayState.h"
#include "Util.h"
#include "BasicProjectile.h"

#include <SFML/Graphics.hpp>

BasicTower::BasicTower(PlayState& _state) : m_state (_state), m_towerPlaced(false) {
	// Initialize shape
	float size = 50.f;
	m_shape.setSize(sf::Vector2f(size, size));
	m_shape.setOrigin(sf::Vector2f(size / 2.f, size / 2.f));

	m_shape.setFillColor(sf::Color(50, 50, 50, 255));

	// Initialize range shape
	m_rangeShape.setRadius(TOWER_RANGE);
	m_rangeShape.setOrigin(TOWER_RANGE, TOWER_RANGE);

	m_rangeShape.setFillColor(sf::Color(0, 200, 0, 100));
	m_rangeShape.setOutlineColor(sf::Color(0, 150, 0, 100));
	m_rangeShape.setOutlineThickness(2.f);
}


BasicTower::~BasicTower() {
}

void BasicTower::input() {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(Display::getWindow());

	if (Display::isInWindow(mousePosition.x, mousePosition.y) && !m_towerPlaced) {
		// Get position on grid
		int gridX = mousePosition.x / GameSettings::BLOCK_SIZE;
		int gridY = mousePosition.y / GameSettings::BLOCK_SIZE;

		if (gridX < m_state.getMap().getMapWidth() && gridY < m_state.getMap().getMapHeight()) {
			sf::Vector2f position(gridX * GameSettings::BLOCK_SIZE + GameSettings::BLOCK_SIZE / 2.f, gridY * GameSettings::BLOCK_SIZE + GameSettings::BLOCK_SIZE / 2.f);
			m_shape.setPosition(position);
			m_rangeShape.setPosition(position);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			int gridPositionX = m_shape.getPosition().x / GameSettings::BLOCK_SIZE;
			int gridPositionY = m_shape.getPosition().y / GameSettings::BLOCK_SIZE;

			if (m_state.getMap().getMapData(gridPositionX, gridPositionY) == Map::HIGH_TERRAIN) {
				m_towerPlaced = true;
			}
		}
	}

}

void BasicTower::update(float _dt) {
	if (m_towerPlaced) {
		static sf::Clock timer;

		// Shoot
		if (timer.getElapsedTime().asSeconds() >= TOWER_SHOOT_PERIOD) {
			std::vector<Enemy*> enemiesInRange = m_state.getEnemiesInRange(m_shape.getPosition(), TOWER_RANGE);
			if (enemiesInRange.size() > 0) {
				// Shoot at enemy
				sf::Vector2f destination = enemiesInRange[0]->getPosition();
				m_state.addProjectile(new BasicProjectile(m_state, destination, m_shape.getPosition()));

				timer.restart();
			}
		}
	}
}

void BasicTower::draw() {
	Display::draw(m_rangeShape);
	Display::draw(m_shape);
}
