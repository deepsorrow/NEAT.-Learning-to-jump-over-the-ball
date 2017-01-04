#ifndef POLYGONS_H
#define POLYGONS_H
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
static const float SCALE = 29.0f;

class Polygon
{
    public:
      void CreateSfpolygon(std::vector<float> &coordinates, sf::Color color, float transparency);
      void CreateB2polygon(b2World &world, std::vector<float> &coordinates, b2Vec2 pos);
      void CreateBall(float radius, sf::Color color);
      void CreateRevJoint(b2World &world, b2Body *bodyA, b2Body *bodyB, b2Vec2 anchorCorrection);
      b2Body *poly;
      sf::ConvexShape *sfpolygon;
      b2RevoluteJointDef *jd;


    private:
};

#endif
