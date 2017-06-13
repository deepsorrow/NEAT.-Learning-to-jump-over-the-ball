#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <string>
#include "polygons.h"
#include "ball.h"
#include "genus.h"

#define BOUNDARY_BITS 0x002
#define BALL_BITS 0x001

class Environment
{
public:
	Environment();
	auto CreateB2bounds(b2World *world) -> void;
	auto CreateSfbounds() -> void;
	auto CreateSfHeightLine() -> void;
	auto CreateSfMaxHeightLine() -> void;
	auto CreateSfDot() -> void;
	auto getInfoString(std::vector<double> &outputVals, const double Bestfitness, const int iteration,
	       const int generation, const int bestGeneration, const std::size_t GenusIndex, const Specie &bestSpecie,
		   const bool &IsSpeededUp, const bool &IsSpeciesVisible) -> void;
	auto MoveToInitialState(b2Body *bodyA,  const b2Vec2 A) -> void;

	auto operator=(Environment &a) -> void;

	b2World *world;
	b2Body *BodyGround;
	sf::RectangleShape groundsf;
	sf::RectangleShape leftwall;
	sf::RectangleShape rightwall;
	sf::RectangleShape ceiling;
	sf::RectangleShape heightLine;
	sf::RectangleShape MaxheightLine;
	sf::CircleShape Ball;
	sf::CircleShape Dot;
	sf::Text text;
	sf::Font font;
	b2Fixture* GroundFix;
	const float RotateConst = 1.2f;


private:
	std::size_t TimeAfterPressedKey = 0;
	bool TrainingSpeed = false;
	b2Body *LeftWall;
	b2Body *RightWall;
	b2Body *Ceiling;
	b2Vec2 Gravity;

};

#endif // ENVIRONMENT_H
