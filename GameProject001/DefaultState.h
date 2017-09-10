#pragma once
#include "GameState.h"
#include "Application.h"

#include <SFML/Graphics.hpp>

class DefaultState : public GameState {
	Application& m_app;
	sf::Texture m_logoTexture;
	sf::Sprite m_logoSprite;
public:
	DefaultState(Application& _app);
	~DefaultState();

	virtual void input() override;
	virtual void update(float _dt) override;
	virtual void draw() override;
};

