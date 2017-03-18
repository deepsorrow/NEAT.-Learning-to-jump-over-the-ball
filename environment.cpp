#include "environment.h"
#include <sstream>
#include <iostream>
#include "windowControl.h"

#define RADTODEG 57.295779513082320876f

using namespace Poly;

Environment::Environment()
{
	Gravity = b2Vec2(0.f, 9.8f);
	world = new b2World(Gravity);

	if (!font.loadFromFile("alpha.ttf"))
		std::cerr << "Font didn't load properly.";

	sf::Color color = sf::Color::Black;
	text.setFont(font);
	text.setCharacterSize(45);
	text.setFillColor(color);
	text.setString("nothingToShowYet");
}

auto Environment::CreateSfbounds() -> void
{
        groundsf = sf::RectangleShape(sf::Vector2f(1280.0f,15.0f));
        groundsf.setFillColor(sf::Color(0,110,150,150));
        groundsf.setPosition(sf::Vector2f(SCALE * BodyGround->GetPosition().x, SCALE * BodyGround->GetPosition().y-15.0f));

        leftwall = sf::RectangleShape(sf::Vector2f(13.0f, 1280.0f));
        leftwall.setFillColor(sf::Color(220,210,150,150));
        leftwall.setPosition(sf::Vector2f(SCALE * LeftWall->GetPosition().x, SCALE * LeftWall->GetPosition().y));

        rightwall = sf::RectangleShape(sf::Vector2f(-13.0f, 1280.0f));
        rightwall.setFillColor(sf::Color(220,210,150,150));
        rightwall.setPosition(sf::Vector2f(SCALE * RightWall->GetPosition().x, SCALE * RightWall->GetPosition().y));

        ceiling = sf::RectangleShape(sf::Vector2f(1280.0f, 5.0f));
        ceiling.setFillColor(sf::Color(0,110,150,150));
        ceiling.setPosition(sf::Vector2f(SCALE * Ceiling->GetPosition().x, SCALE * Ceiling->GetPosition().y));
}

auto Environment::CreateSfHeightLine() -> void
{
    heightLine = sf::RectangleShape(sf::Vector2f(1280.0f,2.0f));
    heightLine.setFillColor(sf::Color(255,0,0,50));
}

auto Environment::CreateSfMaxHeightLine() -> void
{
    MaxheightLine = sf::RectangleShape(sf::Vector2f(1280.0f,3.0f));
    MaxheightLine.setFillColor(sf::Color(255,50,50,120));
}

auto Environment::CreateSfDot() -> void
{
    Dot = sf::CircleShape(5.0f);
    Dot.setFillColor(sf::Color(255,0,255,255));
}

auto Environment::getInfoString(std::vector<double> &outputVals, const double Bestfitness, const int iteration,
	const int generation, const int bestGeneration, const std::size_t GenusIndex, const Specie &bestSpecie, const bool &IsSpeededUp,
	const bool &IsSpeciesVisible) -> void
{
    std::ostringstream ss;
    ss.str("");

	ss.precision(0);
	ss << "\tGeneration = " << generation;

		if (!IsSpeededUp)
			ss << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tPress [R] to speed simulation up" << std::endl;
		else
			ss << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tPress [R] to slow simulation down" << std::endl;

	ss << "\tGenus = " << GenusIndex + 1;

		if (!IsSpeciesVisible)
			ss << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t     Press [S] to see all species" << std::endl;
		else
			ss << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t     Press [S] to hide most species" << std::endl;

	ss << "\tBestFitness = " << std::fixed << Bestfitness << std::endl;

	ss.precision(4);
	ss  << "\tNeuralNetwork outputs:" << std::endl
		<< "\t[0] = " << std::fixed << outputVals[0] << std::endl
		<< "\t[1] = " << std::fixed << outputVals[1] << std::endl
		<< "\t[2] = " << std::fixed << outputVals[2] << std::endl
		<< "\t[3] = " << std::fixed << outputVals[3] << std::endl;

    text.setString(ss.str());
}

auto Environment::MoveToInitialState(b2Body *bodyA, const b2Vec2 A) -> void
{
	 bodyA->SetTransform(A,0.0f);
	 bodyA->SetAngularVelocity(0.0f);
	 bodyA->SetLinearVelocity(b2Vec2(0.0f,0.0f));
}

auto Environment::CreateB2bounds(b2World *world) -> void
{
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(0.0f, 25.0f);
        BodyDef.type = b2_staticBody;
        BodyGround = world->CreateBody(&BodyDef);

        BodyDef.position = b2Vec2(0.0f,0.0f);
        LeftWall = world->CreateBody(&BodyDef);

        BodyDef.position = b2Vec2(1280.0f/SCALE, 0.0f/SCALE);
        RightWall = world->CreateBody(&BodyDef);

        BodyDef.position = b2Vec2(0.0f,0.0);
        Ceiling = world->CreateBody(&BodyDef);

        b2PolygonShape Shape;
        Shape.SetAsBox(1280.0f/SCALE, 15.0f/SCALE);

        b2FixtureDef FixtureDef;
        FixtureDef.density = 1.0f;
        FixtureDef.restitution = 0.0f;
        FixtureDef.friction = 0.5f;
        FixtureDef.shape = &Shape;
		FixtureDef.filter.categoryBits = BOUNDARY_BITS;
        GroundFix = BodyGround->CreateFixture(&FixtureDef);


        b2FixtureDef LeftWallFix;
        LeftWallFix.shape = &Shape;
        Shape.SetAsBox(13.0f/SCALE,720.0f/SCALE);
		LeftWallFix.filter.categoryBits = BOUNDARY_BITS;
        LeftWall->CreateFixture(&LeftWallFix);

        b2FixtureDef RightWallFix;
        RightWallFix.shape = &Shape;
		RightWallFix.filter.categoryBits = BOUNDARY_BITS;
        RightWall->CreateFixture(&RightWallFix);

        b2FixtureDef CeilingFix;
        Shape.SetAsBox(1280.0f/SCALE, 5.0f/SCALE);
        CeilingFix.shape = &Shape;
		CeilingFix.filter.categoryBits = BOUNDARY_BITS;
	//	CeilingFix.filter.maskBits = BALL_BITS;
        Ceiling->CreateFixture(&CeilingFix);
}

auto Environment::operator=(Environment & a) -> void
{
	world = a.world;
	BodyGround = a.BodyGround;
	GroundFix = a.GroundFix;
	LeftWall = a.LeftWall;
	RightWall = a.RightWall;
	Ceiling = a.Ceiling;
	TrainingSpeed = a.TrainingSpeed;
	TimeAfterPressedKey = a.TimeAfterPressedKey;
}
