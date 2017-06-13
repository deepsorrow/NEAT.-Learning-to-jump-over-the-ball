#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <string>
#define RADTODEG 57.295779513082320876f

static const float SCALE = 29.0f;

namespace Poly {

	class Polygon
	{
	public:
		Polygon() = default;
		auto CreateSfpolygon(std::vector<float> &coordinates, sf::Color color, sf::Uint8 transparency) -> void;
		auto CreateB2polygon(b2World *world, std::vector<float> &coordinates, b2Vec2 pos, int category) -> void;
		//      auto CreateBall(const float & radius, b2World *world, const b2Vec2 & pos) -> void;
		auto CreateRevJoint(b2World *world, b2Body *bodyB, b2Vec2 anchorCorrection, float AngleLimit) -> void;
		b2Body *poly;
		sf::ConvexShape sfpolygon;
		b2Fixture* polyFix;
		b2RevoluteJoint* Joint;
	private:
		b2RevoluteJointDef jd;
		float MotorSpeed;
	};
}
