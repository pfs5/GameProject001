#include "stdafx.h"
#include "Application.h"
#include "Util.h"
#include "Display.h"
#include <SFML/System/Clock.hpp>

void calculateFPS(bool _print_fps) {
	static sf::Clock timer;
	static sf::Clock printTimer;
	static auto numFrames = 0;

	numFrames++;

	if (printTimer.getElapsedTime().asSeconds() >= 1.0f) {
		auto fps = (float)numFrames / timer.getElapsedTime().asSeconds();
		printTimer.restart();
		if (_print_fps) {
			Util::printMessage(std::to_string(fps));
		}

		numFrames = 0;
		timer.restart();
	}
}

Application::Application() {
	Display::init();
}


Application::~Application() {
	// Clear game states
	while (!m_gameStates.empty()) {
		delete m_gameStates.top();
		m_gameStates.pop();
	}
}

void Application::runMainLoop() {
	sf::Clock clock;
	sf::Time accumulator;
	sf::Time dt = sf::seconds(1.f / Display::UPS);
	sf::Time max_acc = sf::seconds(0.2f);

	while (Display::isOpen()) {
		Display::checkWindowEvents();
		Display::clear();

		if (!m_gameStates.empty()) {
			m_gameStates.top()->input();
		}
		else {
			return;
		}

		// Physics
		accumulator += clock.restart();

		while (accumulator > dt) {
			if (!m_gameStates.empty()) {
				m_gameStates.top()->update(dt.asSeconds());
			}
			else {
				return;
			}

			accumulator -= dt;
		}

		// Rendering
		if (!m_gameStates.empty()) {
			m_gameStates.top()->draw();
		}
		else {
			return;
		}

		calculateFPS(false);
		Display::display();
	}
}

	void Application::addGameState(GameState *_gameState) {
		m_gameStates.push(_gameState);
	}

	void Application::popGameState() {
		delete m_gameStates.top();
		m_gameStates.pop();
	}