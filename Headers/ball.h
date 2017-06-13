#pragma once
#include "environment.h"
const float ballRadius = 1.0f;

class Ball
{
public:
	explicit Ball(const float &radius);
	explicit Ball(const float &radius, b2World *world, const b2Vec2 &pos);
	auto CreateBall(const float &radius, b2World *world, const b2Vec2 &pos) -> void;
	auto getBallFix() -> b2Fixture* { return BallFix; }
	bool hasBeenTouched = false;
	b2Body *b2Ball;
	sf::CircleShape SfBall;
private:
	auto SetSFAppearance() -> void;
	b2Fixture* BallFix;
};
