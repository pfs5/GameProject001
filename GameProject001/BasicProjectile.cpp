#include "stdafx.h"
#include "BasicProjectile.h"
#include "Util.h"
#include "Display.h"

BasicProjectile::BasicProjectile(PlayState& _state, const sf::Vector2f& _destination, const sf::Vector2f& _position) : m_state(_state), m_destination(_destination) {
	// Initialize shape
	m_shape.setRadius(5.f);
	m_shape.setFillColor(sf::Color::Yellow);
	m_shape.setPosition(_position);
}

BasicProjectile::~BasicProjectile() {
}

void BasicProjectile::input() {
}

void BasicProjectile::update(float _dt) {
	sf::Vector2f direction = m_destination - m_shape.getPosition();

	// Check destination reached
	if (Util::magnitude(direction) < 5.f) {
		m_state.notify(this);
	}

	m_shape.move(Util::normalize(direction) * SPEED);

}

void BasicProjectile::draw() {
	Display::draw(m_shape);
}
