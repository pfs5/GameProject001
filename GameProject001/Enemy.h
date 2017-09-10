#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
	virtual ~Enemy() {};

	virtual void input() = 0;
	virtual void update(float _dt) = 0;
	virtual void draw() = 0;

	virtual const sf::Vector2f& getPosition() = 0;
};