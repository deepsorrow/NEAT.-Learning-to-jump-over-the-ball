#include "polygons.h"
#include "environment.h"
#include <vector>
#include <SFML/Graphics.hpp>
#define RADTODEG 57.295779513082320876f

void Polygon::CreateSfpolygon(std::vector<float> &coordinates, sf::Color color, float transparency)
{
    sfpolygon = new sf::ConvexShape;

    int verticies = coordinates.size() / 2;
    sfpolygon->setPointCount(verticies);

    for(int i=0, j = 0; i<verticies; i++, j+=2)
    {
        sfpolygon->setPoint(i, sf::Vector2f(coordinates[j]*SCALE,coordinates[j+1]*SCALE));
    }

        sfpolygon->setFillColor(sf::Color(color.r, color.b, color.g, transparency));
        sfpolygon->setOutlineColor(sf::Color::Black);
        sfpolygon->setOutlineThickness(1.5f);
}

void Polygon::CreateB2polygon(b2World &world, std::vector<float> &coordinates, b2Vec2 pos)
{
    b2BodyDef PolyDef;
    PolyDef.position = pos;
    PolyDef.type = b2_dynamicBody;

    poly = world.CreateBody(&PolyDef);

    int verticies = coordinates.size() / 2;
    b2Vec2 setVerc[verticies];

    //Set coordinates of our verticies
    for(int i=0, j=0; i<=verticies; i++, j+=2)
    {
        setVerc[i].Set(coordinates[j],coordinates[j+1]);
    }

    b2PolygonShape PolyShape;
    PolyShape.Set(setVerc, verticies);

    b2FixtureDef PolyFixture;
    PolyFixture.density = 0.5f;
    PolyFixture.restitution = 0.01f;
    PolyFixture.friction = 0.3f;
    PolyFixture.shape = &PolyShape;
    poly->CreateFixture(&PolyFixture);
}

void Polygon::CreateRevJoint(b2World &world, b2Body *bodyA, b2Body *bodyB, b2Vec2 anchorCorrection)
{
    jd = new b2RevoluteJointDef;
    jd->Initialize(bodyA,bodyB,bodyA->GetPosition()-anchorCorrection);
    jd->collideConnected = true;
    world.CreateJoint(jd);
}
