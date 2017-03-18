#include "Ball.h"

Ball::Ball(const float &radius)
{
	SfBall = sf::CircleShape(radius*SCALE);
}

Ball::Ball(const float &radius, b2World *world, const b2Vec2 &pos)
{
	SfBall = sf::CircleShape(radius*SCALE);
	SetSFAppearance();

	CreateBall(radius, world, pos);
}

auto Ball::CreateBall(const float & radius, b2World *world, const b2Vec2 & pos) -> void
{
	b2BodyDef BallDef;
	BallDef.position = pos;
	BallDef.type = b2_dynamicBody;

	b2Ball = world->CreateBody(&BallDef);
	b2Ball->SetUserData(this);

	b2CircleShape circle;
	circle.m_radius = radius;

	b2FixtureDef BallFixDef;
	BallFixDef.density = 111.0f;
	BallFixDef.restitution = 0.01f;
	BallFixDef.friction = 0.6f;
	BallFixDef.shape = &circle;
	BallFixDef.filter.categoryBits = BALL_BITS;
	BallFixDef.filter.maskBits = BOUNDARY_BITS;
	BallFix = b2Ball->CreateFixture(&BallFixDef);
}

auto Ball::SetSFAppearance() -> void
{
	SfBall.setFillColor(sf::Color(255, 0, 0, 160));
	SfBall.setOutlineColor(sf::Color::Black);
	SfBall.setOutlineThickness(1.5f);
}
