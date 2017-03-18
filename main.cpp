#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <utility>
#include <algorithm>
#include <deque>
#include <thread>
#include <future>
#include "boost\timer\timer.hpp"
#include "termcolor\termcolor.hpp"
#include "modelManager.h"
#include "genusManager.h"
#include "windowControl.h"


struct Settings {
	std::vector<float> coordinates1, coordinates2, coordinates3;
	std::size_t GenusSize = 10;
	const std::size_t GenusPopulation = 13;
	const b2Vec2 SpawnPoint = b2Vec2(10.0f, 18.0f);
	const b2Vec2 BallSpawnPos = b2Vec2(44.0f, 23.5f + ballRadius);

	explicit Settings() { AddCoordinates(); }
private:
	auto AddCoordinates() -> void;
};

void CreateEnvironment(Environment& env);

int main()
{
	srand((unsigned int)time(NULL)); // to make all simulation unique

	int iteration = 0,
		generation = 1,
		bestGeneration = 1,
		genusIndex = 0;
	double maxfitness = 0;

	WindowControl w;
	Settings s;
	Environment env;
	Ball ball(ballRadius, env.world, s.BallSpawnPos);
	CreateEnvironment(env);

	std::vector<std::vector<float>> commonCords = { s.coordinates1,s.coordinates2,s.coordinates3 };
	std::vector<double> inputVals(12), outputVals(4);

	Representative::ModelManager Creatures(s.GenusPopulation, s.SpawnPoint, env.world, commonCords);
	GenusManager Life(s.GenusSize, s.GenusPopulation-1, inputVals, outputVals);
	Specie bestSpecie = Life[0].GetFittestOrganism();
	
	std::cout << termcolor::white << "Evolving Neural Network through Augmenting Topologies with Genetic Algorithm \t\tKropotov Alexey. 10th grade.";
	std::cout << termcolor::cyan << "\nFor scientific-research project in Lyceum #84. \t\t\t\t\t\t27.02.2017" << termcolor::reset;
	std::cout << termcolor::cyan << "\n\t\t\t\t\t\t\t\t\t\t\tNovokuznetsk, Russia" << termcolor::reset;
	std::cout.precision(0);

    while(w.GetWindow().isOpen()){
        env.world->Step(1/60.0f, 4, 3);
		w.Step();
        
		Creatures.Step(Life[genusIndex], bestSpecie, ball);
		Creatures.DrawSfModels(ball);
		Creatures.UpdateFitnesses(Life[genusIndex], ball, env.BodyGround, env.GroundFix);
		outputVals = Creatures.outputs;

		ball.b2Ball->SetLinearVelocity(b2Vec2(-9.0f, 0.0f));
		if (ball.b2Ball->GetPosition().x < 1.5f) {
			if(generation > 7)
				Creatures.UpdateBallFitness(Life[genusIndex]);
			env.MoveToInitialState(ball.b2Ball, s.BallSpawnPos);
		}

		iteration++;
        if(iteration >= 2570 && w.shouldIterationIncrement)
        {
			iteration = 0;
			if (maxfitness < Life[genusIndex].GetFittestOrganism().GetFitness()) {
				bestGeneration = generation;
				bestSpecie = Life[genusIndex].GetFittestOrganism();
				auto previousMaxFitness = std::max(1.0, maxfitness);
				maxfitness = Life[genusIndex].GetFittestOrganism().GetFitness();
				auto progress = (maxfitness / previousMaxFitness) * 100 - 100;
				if(progress >= 1)
				std::cout << termcolor::green << "\n[SUCCESS]:" << termcolor::reset << " Fitness has progressed on "
					<< std::fixed << progress << "%!";
			}

			if (genusIndex + 1 < s.GenusSize) {
				Life[genusIndex].Evolve();
				genusIndex++;
			}
			else {
				genusIndex = 0;
			//	if (Random::DidChanceOccure(0.03)) {
			//		Life.AddNewInterspecieGenus();
			//		std::cout << termcolor::magenta << "\n[IMPROVEMENT]: New Genus has been created.";
			//		if (Life.GetGenusesSize() > s.GenusSize) //if worst genus didn't pop out
			//			s.GenusSize++;
			//		else
			//			std::cout << "\n[IMPROVEMENT]: Worst genus has extincted.";
			//	
			//		std::cout << termcolor::reset;
			//	}
				
				std::cout << "\n\nGeneration passed: [" << generation << "]\nMost profitable generation was: " << bestGeneration;
				std::cout << "\nBall hasn't been touched: " << Creatures.GetAndResetTouchedCounter() << " times!";
				std::cout << "\nBest Fitness of all time: " << maxfitness;
				std::cout << termcolor::reset;
				std::cout << "\n";

				generation++;
			}

			Environment temp;
			env = temp;
			CreateEnvironment(env);
			ball = Ball(ballRadius, env.world, s.BallSpawnPos);
			env.MoveToInitialState(ball.b2Ball, s.BallSpawnPos);
			Creatures.MoveToInitialState(env.world);

		}
        
        env.getInfoString(outputVals, static_cast<float>(maxfitness), iteration, generation, bestGeneration, genusIndex,
			bestSpecie, w.IsSimulationSpeededUp(), w.isSpeciesVisible);

		w.GetWindow().clear(sf::Color::White);
		w.GetWindow().draw(env.text);
		w.GetWindow().draw(env.groundsf);
		w.GetWindow().draw(env.leftwall);
		w.GetWindow().draw(env.rightwall);
		w.GetWindow().draw(env.ceiling);
		w.GetWindow().draw(env.heightLine);
		w.GetWindow().draw(env.MaxheightLine);

			for (std::size_t j = 0U; j < Creatures.models.back().polys.size(); ++j)
				w.GetWindow().draw(Creatures.models.back().polys[j].sfpolygon);

			if (w.isSpeciesVisible) {
				for (std::size_t i = 0U; i < Creatures.models.size(); ++i)
					for (std::size_t j = 0U; j < Creatures.models[i].polys.size(); ++j)
						w.GetWindow().draw(Creatures.models[i].polys[j].sfpolygon);
			}

		w.GetWindow().draw(ball.SfBall);
		w.GetWindow().display();
	}
}

auto Settings::AddCoordinates() -> void
{
	coordinates1.push_back(0.0f);
	coordinates1.push_back(0.0f);
	coordinates1.push_back(1.0f);
	coordinates1.push_back(1.0f);
	coordinates1.push_back(3.0f);
	coordinates1.push_back(1.0f);
	coordinates1.push_back(3.0f);
	coordinates1.push_back(0.0f);

	coordinates2.push_back(0.0f);
	coordinates2.push_back(0.0f);
	coordinates2.push_back(1.0f);
	coordinates2.push_back(2.0f);
	coordinates2.push_back(2.0f);
	coordinates2.push_back(2.0f);
	coordinates2.push_back(2.0f);
	coordinates2.push_back(0.0f);

	coordinates3.push_back(0.0f);
	coordinates3.push_back(0.0f);
	coordinates3.push_back(0.0f);
	coordinates3.push_back(2.0f);
	coordinates3.push_back(2.0f);
	coordinates3.push_back(2.0f);
	coordinates3.push_back(1.0f);
	coordinates3.push_back(-1.0f);
}

void CreateEnvironment(Environment& env)
{
	env.CreateB2bounds(env.world);
	env.CreateSfbounds();
	env.CreateSfHeightLine();
	env.CreateSfMaxHeightLine();
	env.CreateSfDot();
}