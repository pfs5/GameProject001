#include "stdafx.h"
#include "DefaultState.h"
#include "PlayState.h"
#include "Display.h"
#include "Util.h"
#include <SFML/Graphics.hpp>


DefaultState::DefaultState(Application& _app) : m_app (_app) {
	if (!m_logoTexture.loadFromFile("logo.png")) {
		Util::printMessage("[DefaultState] Error loading logo.png");
	}

	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setTextureRect(sf::IntRect(0.f, 0.f, m_logoTexture.getSize().x, m_logoTexture.getSize().y));
	
	m_logoSprite.setOrigin(m_logoTexture.getSize().x / 2, m_logoTexture.getSize().y / 2);
	m_logoSprite.setPosition(sf::Vector2f(Display::WIDTH / 2, Display::HEIGHT / 2));
}


DefaultState::~DefaultState() {
}

void DefaultState::input() {
	// Start game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		m_app.addGameState(new PlayState(m_app));
	}
}

void DefaultState::update(float _dt) {

}

void DefaultState::draw() {
	Display::draw(m_logoSprite);
}