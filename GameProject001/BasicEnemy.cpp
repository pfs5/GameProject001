#include "stdafx.h"
#include "BasicEnemy.h"
#include "Util.h"
#include "Display.h"
#include "GameSettings.h"

BasicEnemy::BasicEnemy(PlayState& _state, GraphNode *_mapGraph) : m_state(_state), m_currentMapNode(_mapGraph) {
	// Init shape
	m_shape.setSize(sf::Vector2f(20.f, 20.f));
	m_shape.setOrigin(sf::Vector2f(10.f, 11.f));

	m_shape.setPosition(m_currentMapNode->x * GameSettings::BLOCK_SIZE + GameSettings::BLOCK_SIZE / 2, m_currentMapNode->y * GameSettings::BLOCK_SIZE + GameSettings::BLOCK_SIZE / 2);
	m_currentMapNode = m_currentMapNode->nextNodes[0];

	m_shape.setFillColor(sf::Color::Red);
}


BasicEnemy::~BasicEnemy() {
}

void BasicEnemy::input() {
}

void BasicEnemy::update(float _dt) {
	sf::Vector2f destination(m_currentMapNode->x * GameSettings::BLOCK_SIZE + GameSettings::BLOCK_SIZE / 2, 
		m_currentMapNode->y * GameSettings::BLOCK_SIZE + GameSettings::BLOCK_SIZE / 2);

	// Move towards destination
	sf::Vector2f direction = Util::normalize(destination - m_shape.getPosition());
	m_shape.move(direction * SPEED * _dt);

	// Check if reached
	sf::Vector2f distance = destination - m_shape.getPosition();
	if (Util::magnitude(distance) < 1.f) {
		if (m_currentMapNode->nextNodes.size() == 0) {
			// Final node
			m_state.notify(this);
			return;
		}
		// Next destination
		int nextNode = Util::randomi(0, m_currentMapNode->nextNodes.size() - 1);
		m_currentMapNode = m_currentMapNode->nextNodes[nextNode];
	}
}

void BasicEnemy::draw() {
	Display::draw(m_shape);
}

const sf::Vector2f & BasicEnemy::getPosition() {
	return m_shape.getPosition();
}
