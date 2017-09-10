#pragma once

class Projectile {
public:
	virtual ~Projectile() {};

	virtual void input() = 0;
	virtual void update(float _dt) = 0;
	virtual void draw() = 0;
};