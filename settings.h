#pragma once
#include <vector>
#include "environment.h"
#include "Box2D\Box2D.h"

struct Settings {
	static std::vector<float> coordinates1, coordinates2, coordinates3;
	const static std::size_t GenusPopulation = 14;
	const static std::size_t GenusSize = 10;
	static b2Vec2 SpawnPoint;
	static b2Vec2 BallSpawnPos;
	explicit Settings() {
		SpawnPoint = b2Vec2(10.0f, 18.0f);
		BallSpawnPos = b2Vec2(44.0f, 23.5f + ballRadius);
	}
};

struct Counters {
	static int iteration;
	static int generation;
	static int bestGeneration;
	static int GenusIndex;
	static int bestGenusI;
	static int currFitnessOfbestGenus;
	static double maxfitness;
	explicit Counters() {
		iteration = 0;
		generation = 1;
		bestGeneration = 1;
		GenusIndex = 0;
		bestGenusI = 0;
		currFitnessOfbestGenus = 0;
		maxfitness = 0;
	}
};
