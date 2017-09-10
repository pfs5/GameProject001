#pragma once
#include "Tower.h"
#include "PlayState.h"
#include "GameSettings.h"
#include <SFML/Graphics.hpp>

class BasicTower : public Tower {
	const float TOWER_RANGE = 2.f * GameSettings::BLOCK_SIZE;
	const float TOWER_SHOOT_PERIOD = 0.5f;

	PlayState& m_state;

	sf::RectangleShape m_shape;
	sf::CircleShape m_rangeShape;

	bool m_towerPlaced;
public:
	BasicTower(PlayState& _state);
	~BasicTower();

	virtual void input() override;
	virtual void update(float _dt) override;
	virtual void draw() override;
};

