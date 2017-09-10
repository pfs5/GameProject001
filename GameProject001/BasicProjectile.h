#pragma once
#include "Projectile.h"
#include "PlayState.h"
#include <SFML/Graphics.hpp>

class BasicProjectile : public Projectile{
	const float SPEED = 5.f;

	PlayState& m_state;

	sf::CircleShape m_shape;

	sf::Vector2f m_destination;
public:
	BasicProjectile(PlayState& _state, const sf::Vector2f& _destination, const sf::Vector2f& _position);
	~BasicProjectile();

	virtual void input() override;
	virtual void update(float _dt) override;
	virtual void draw() override;
};

