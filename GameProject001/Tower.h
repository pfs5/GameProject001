#pragma once

class Tower {
public:
	virtual ~Tower() {};

	virtual void input() = 0;
	virtual void update(float _dt) = 0;
	virtual void draw() = 0;
};