#pragma once
#include "Enemy.h"
#include "Map.h"
#include "PlayState.h"
#include <SFML/Graphics.hpp>

class BasicEnemy : public Enemy {
	const float SPEED = 100.f;

	PlayState& m_state;

	sf::RectangleShape m_shape;
	GraphNode *m_currentMapNode;
public:
	BasicEnemy(PlayState& _state, GraphNode *_mapGraph);
	~BasicEnemy();
	
	virtual void input();
	virtual void update(float _dt);
	virtual void draw();

	virtual const sf::Vector2f& getPosition() override;
};

