#include "environment.h"
#include "polygons.h"
#include <sstream>
#include <iostream>

#define RADTODEG 57.295779513082320876f

void Environment::CreateSfbounds()
{
        groundsf = new sf::RectangleShape(sf::Vector2f(1280.0f,15.0f));
        groundsf->setFillColor(sf::Color(0,110,150,150));
        groundsf->setPosition(sf::Vector2f(SCALE * BodyGround->GetPosition().x, SCALE * BodyGround->GetPosition().y-15.0f));

        leftwall = new sf::RectangleShape(sf::Vector2f(13.0f, 1280.0f));
        leftwall->setFillColor(sf::Color(220,210,150,150));
        leftwall->setPosition(sf::Vector2f(SCALE * LeftWall->GetPosition().x, SCALE * LeftWall->GetPosition().y));

        rightwall = new sf::RectangleShape(sf::Vector2f(-13.0f, 1280.0f));
        rightwall->setFillColor(sf::Color(220,210,150,150));
        rightwall->setPosition(sf::Vector2f(SCALE * RightWall->GetPosition().x, SCALE * RightWall->GetPosition().y));

        ceiling = new sf::RectangleShape(sf::Vector2f(1280.0f, 5.0f));
        ceiling->setFillColor(sf::Color(0,110,150,150));
        ceiling->setPosition(sf::Vector2f(SCALE * Ceiling->GetPosition().x, SCALE * Ceiling->GetPosition().y));
}

void Environment::CreateSfHeightLine()
{
    heightLine = new sf::RectangleShape(sf::Vector2f(1280.0f,2.0f));
    heightLine->setFillColor(sf::Color(255,0,0,50));
}

void Environment::CreateSfMaxHeightLine()
{
    MaxheightLine = new sf::RectangleShape(sf::Vector2f(1280.0f,3.0f));
    MaxheightLine->setFillColor(sf::Color(255,50,50,120));
}

void Environment::CreateSfDot()
{
    Dot = new sf::CircleShape(15.0f);
    Dot->setFillColor(sf::Color(255,255,255,160));
}

void Environment::getInfoString(b2Body *bodyA, b2Body *bodyB, b2Body *bodyC, b2Body *ground, std::vector<double> &inputVals,
                                std::vector<double> &outputVals, double fitness, int iteration, int generation, int bestGeneration, double maxFitness)
{
    std::ostringstream ss;
    ss.str("");
    ss //<< "                polygon1_x = " << bodyA->GetPosition().x << std::endl
  //     << "                polygon1_y = " << bodyA->GetPosition().y << std::endl
  //     << "\t-> polygon1_ang = " << inputVals[0] << std::endl
 //      << "          polygon2_x = " << bodyB->GetPosition().x << std::endl
 //      << "          polygon2_y = " << bodyB->GetPosition().y << std::endl
 //      << "\t-> polygon2_ang = " << inputVals[1] << std::endl
//       << "    polygon3_x = " << bodyC->GetPosition().x << std::endl
//       << "    polygon3_y = " << bodyC->GetPosition().y << std::endl
//       << "\t-> polygon3_ang = " << inputVals[2] << std::endl
//       << "\t-> height = "<< inputVals[3] << std::endl
//       << "\titeration = " << iteration << std::endl
//       << "\tFitness = " << fitness << std::endl
       << "\tMaxFitness = " << maxFitness << std::endl
       << "\tGeneration = " << generation << std::endl
       << "\tBestGeneration = " << bestGeneration << std::endl
       << "\t[0] = " << std::fixed << outputVals[0] << std::endl
       << "\t[1] = " << outputVals[1] << std::endl
       << "\t[2] = " << outputVals[2] << std::endl;

    text->setString(ss.str());
}

void Environment::MoveToInitialState(b2Body *bodyA, b2Body *bodyB, b2Body *bodyC, b2Vec2 A, b2Vec2 B, b2Vec2 C)
{
    bodyA->SetTransform(A,0.0f);
    bodyB->SetTransform(B,0.0f);
    bodyC->SetTransform(C,0.0f);
    bodyA->SetAngularVelocity(0.0f);
    bodyB->SetAngularVelocity(0.0f);
    bodyC->SetAngularVelocity(0.0f);
    bodyA->SetLinearVelocity(b2Vec2(0.0f,0.0f));
    bodyB->SetLinearVelocity(b2Vec2(0.0f,0.0f));
    bodyC->SetLinearVelocity(b2Vec2(0.0f,0.0f));
}

void Environment::KeyboardControl(sf::RenderWindow &window)
{
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
        window.setFramerateLimit(99999999);
    else
        window.setFramerateLimit(60);
}

Environment::Environment()
{
    Gravity = new b2Vec2(0.f, 9.8f);
    world = new b2World(*Gravity);
    text = new sf::Text;
    font = new sf::Font;

    font->loadFromFile("/home/rootuser/Documents/QtProjects/NetworkAlgorhitm/coolveticarg.ttf");
    text->setFont(*font);
    text->setCharacterSize(20);
    text->setColor(sf::Color::Black);
    text->setString("nothingToShowYet");
}

void Environment::CreateB2bounds(b2World &world)
{
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(0.0f, 25.0f);
        BodyDef.type = b2_staticBody;
        BodyGround = world.CreateBody(&BodyDef);

        BodyDef.position = b2Vec2(0.0f,0.0f);
        LeftWall = world.CreateBody(&BodyDef);

        BodyDef.position = b2Vec2(1280.0f/SCALE, 0.0f/SCALE);
        RightWall = world.CreateBody(&BodyDef);

        BodyDef.position = b2Vec2(0.0f,0.0);
        Ceiling = world.CreateBody(&BodyDef);

        b2PolygonShape Shape;
        Shape.SetAsBox(1280.0f/SCALE, 15.0f/SCALE);

        b2FixtureDef FixtureDef;
        FixtureDef.density = 1.0f;
        FixtureDef.restitution = 0.0f;
        FixtureDef.friction = 0.5f;
        FixtureDef.shape = &Shape;
        BodyGround->CreateFixture(&FixtureDef);


        b2FixtureDef LeftWallFix;
        LeftWallFix.shape = &Shape;
        Shape.SetAsBox(13.0f/SCALE,720.0f/SCALE);
        LeftWall->CreateFixture(&LeftWallFix);

        b2FixtureDef RightWallFix;
        RightWallFix.shape = &Shape;
        RightWall->CreateFixture(&RightWallFix);

        b2FixtureDef CeilingFix;
        Shape.SetAsBox(1280.0f/SCALE, 5.0f/SCALE);
        CeilingFix.shape = &Shape;
        Ceiling->CreateFixture(&CeilingFix);
}
