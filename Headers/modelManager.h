#pragma once
#include "model.h"
#include "genusManager.h"
#define JUMPFORCE 250.0f

namespace Representative {

	class ModelManager {

	public:
		explicit ModelManager() = default;
		explicit ModelManager(const std::size_t &nSize, const b2Vec2 &newSpawnPoint, b2World *newWorld, const std::vector<std::vector<float>> &coords);
		//explicit ModelManager(std::vector<Model> &new_models) : size(new_models.size()) { models = new_models; }
		auto AddNewModel() -> void;
		auto AddPerfectModel() -> void;
		auto SetSpawnPoint(const b2Vec2 &newSpawnPoint) -> void { SpawnPoint = newSpawnPoint; }
		auto SetCoordinates(const std::vector<std::vector<float>> &coords) -> void { coordinates = coords; }
		auto ToProduceModels() -> void;
		auto SetCategoryBits() -> void;
		auto SetWorld(b2World *newworld) -> void { world = newworld; }
		auto GetAndResetTouchedCounter() -> std::size_t { auto toReturn = touchedCounter; touchedCounter = 0; return toReturn; }
		auto CalculateInputs(Ball &ball) -> void;
		auto MoveModelByOutputs(Genus &life) -> void;
		auto MoveIdealModel(Specie &bestSpecie) -> void;
		auto DrawSfModels(Ball &ball) -> void;
		auto UpdateFitnesses(Genus &life, Ball &ball, b2Body *Ground, b2Fixture *GroundFix) -> void;
		auto MoveToInitialState(b2World* newWorld) -> void;
		auto UpdateBallFitness(Genus &life) -> void;
		auto PunishStagnantModels(Genus &life) -> void;
		auto Step(Genus &life, Specie &bestSpecie, Ball &ball) -> void;
		std::vector<Model> models;
		std::vector<std::vector<bool>> hasBeenTouched;
		std::vector<double> outputs;
	private:
		const std::size_t size;
		std::size_t moduleCount;
		b2World *world;
		std::vector<std::size_t> categoryBits;
		b2Vec2 SpawnPoint;
		std::vector<std::vector<double>> inputs;
		std::vector<std::vector<float>> coordinates;
		std::vector<std::size_t> StagnantTimer;
		std::size_t touchedCounter = 0;
	};

}
