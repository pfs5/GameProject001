#pragma once

class GameState {
public:
	virtual ~GameState() {};

	virtual void input() = 0;
	virtual void update(float _dt) = 0;
	virtual void draw() = 0;
};