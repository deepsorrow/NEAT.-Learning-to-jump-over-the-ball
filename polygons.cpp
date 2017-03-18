#include "polygons.h"
#include "environment.h"
#include <vector>
#include <SFML/Graphics.hpp>

using namespace Poly;

auto Polygon::CreateSfpolygon(std::vector<float> &coordinates, sf::Color color, sf::Uint8 transparency) -> void
{
    auto verticies = coordinates.size() / 2;
    sfpolygon.setPointCount(verticies);

    for(auto i=0, j = 0; i<verticies; i++, j+=2)
    {
        sfpolygon.setPoint(i, sf::Vector2f(coordinates[j]*SCALE,coordinates[j+1]*SCALE));
    }

        sfpolygon.setFillColor(sf::Color(color.r, color.b, color.g, transparency));
        sfpolygon.setOutlineColor(sf::Color::Black);
        sfpolygon.setOutlineThickness(1.5f);
}

auto Polygon::CreateB2polygon(b2World *world, std::vector<float> &coordinates, b2Vec2 pos, int category) -> void
{
    b2BodyDef PolyDef;
    PolyDef.position = pos;
    PolyDef.type = b2_dynamicBody;

    poly = world->CreateBody(&PolyDef);
	poly->SetUserData(this);

	auto verticies = coordinates.size() / 2;
	b2Vec2 *setVerc = new b2Vec2[verticies];

    //Set coordinates of our verticies
    for(auto i=0, j=0; i<verticies; i++, j+=2)
    {
        setVerc[i].Set(coordinates[j],coordinates[j+1]);
    }

    b2PolygonShape PolyShape;
    PolyShape.Set(setVerc, static_cast<int32>(verticies));

	b2FixtureDef PolyFixture;
    PolyFixture.density = 1.0f;
    PolyFixture.restitution = 0.01f;
    PolyFixture.friction = 0.3f;
	PolyFixture.shape = &PolyShape;
	PolyFixture.filter.categoryBits = category;
	PolyFixture.filter.maskBits = BOUNDARY_BITS | category;
    polyFix = poly->CreateFixture(&PolyFixture);
}


auto Polygon::CreateRevJoint(b2World *world, b2Body *bodyB, b2Vec2 anchorCorrection, float AngleLimit) -> void
{
    jd.Initialize(poly,bodyB, poly->GetPosition()-anchorCorrection);
    jd.collideConnected = true;
	jd.enableMotor = true;
	jd.enableLimit = true;
	jd.maxMotorTorque = 400.0f;
	jd.lowerAngle = -AngleLimit / 2;
	jd.upperAngle = AngleLimit / 2;
    Joint = (b2RevoluteJoint*)world->CreateJoint(&jd);
}

/*auto Polygon::CreateBall(const float & radius, b2World *world, const b2Vec2 & pos) -> void
{
	b2BodyDef BallDef;
	BallDef.position = pos;
	BallDef.type = b2_dynamicBody;

	ball = world->CreateBody(&BallDef);

	b2CircleShape Circle;
    Circle.m_radius = radius;

	b2FixtureDef BallFix;
	BallFix.density = 0.5f;
	BallFix.restitution = 0.01f;
	BallFix.friction = 0.3f;
	BallFix.shape = &Circle;
	ball->CreateFixture(&BallFix);
}*/
