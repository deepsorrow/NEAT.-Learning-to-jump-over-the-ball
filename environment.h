#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <string>

class Environment
{
public:
Environment();
void CreateB2bounds(b2World &world);
void CreateSfbounds();
void CreateSfHeightLine();
void CreateSfMaxHeightLine();
void CreateSfDot();
void getInfoString(b2Body *bodyA, b2Body *bodyB, b2Body *bodyC, b2Body *ground, std::vector<double> &inputVals, std::vector<double> &outputVals,
                   double fitness, int iteration, int generation, int bestGeneration, double maxFitness);
void MoveToInitialState(b2Body *bodyA, b2Body *bodyB, b2Body *bodyC, b2Vec2 A, b2Vec2 B, b2Vec2 C);
void KeyboardControl(sf::RenderWindow &window);
b2World *world;
b2Body *BodyGround;
b2Body *LeftWall;
b2Body *RightWall;
b2Body *Ceiling;
sf::RectangleShape *groundsf;
sf::RectangleShape *leftwall;
sf::RectangleShape *rightwall;
sf::RectangleShape *ceiling;
sf::RectangleShape *heightLine;
sf::RectangleShape *MaxheightLine;
sf::CircleShape *Dot;
sf::Text *text;
sf::Font *font;


private:
b2Vec2 *Gravity;

};

#endif // ENVIRONMENT_H
