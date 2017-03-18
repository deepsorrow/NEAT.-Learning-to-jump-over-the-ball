#include "modelManager.h"
#include <fstream>

Representative::ModelManager::ModelManager(const std::size_t &nSize, const b2Vec2 &newSpawnPoint, b2World *newWorld, const std::vector<std::vector<float>> &coords)
	: size(nSize)
{
	SetCoordinates(coords);
	SetSpawnPoint(newSpawnPoint);
	SetWorld(newWorld);
	SetCategoryBits();
	
	ToProduceModels();

	StagnantTimer.resize(models.size());
}

auto Representative::ModelManager::SetCategoryBits() -> void
{
	for (std::size_t i = 0, bit = 0x0004; i < size; i++, bit<<=1)
		categoryBits.push_back(bit);
}

auto Representative::ModelManager::CalculateInputs(Ball &ball) -> void
{
	for (std::size_t i = 0; i < models.size(); i++) {
		inputs.push_back(std::vector<double>());
		for (std::size_t j = 0, c = 0; j < models[i].polys.size(); j++, c++) {
			if (j + 1 < models[i].polys.size()) {
				inputs[i].push_back(abs(models[i].polys[j].Joint->GetJointAngle() / 360));
			}
			inputs[i].push_back(abs(models[i].polys[j].poly->GetAngle()*RADTODEG)/360);
			inputs[i].push_back(abs((models[i].polys[c].poly->GetPosition().x)/35));
			inputs[i].push_back(abs((25-models[i].polys[c].poly->GetPosition().y)/25));
		}
		 inputs[i].push_back(abs(1/(b2Distance(ball.b2Ball->GetPosition(), models[i].polys[1].poly->GetPosition())-5)));
	}
}

auto Representative::ModelManager::Step(Genus &life, Specie &bestSpecie, Ball &ball) -> void
{
	CalculateInputs(ball);
	MoveModelByOutputs(life);
	MoveIdealModel(bestSpecie);
	PunishStagnantModels(life);

	inputs.clear();
}

auto Representative::ModelManager::MoveModelByOutputs(Genus &life) -> void
{
	outputs.clear();
	outputs.resize((models[0].polys.size()-1)*2);

	for (std::size_t j = 0; j < models.size()-1; ++j) {
		life.Species[j].GetOutputs(inputs[j], outputs);

		for (std::size_t i = 0; i < models[j].polys.size() - 1; ++i)
			models[j].polys[i].Joint->SetMotorSpeed(static_cast<float>(outputs[i] - outputs[i + 2])*JUMPFORCE);
	}	
}

auto Representative::ModelManager::MoveIdealModel(Specie &bestSpecie) -> void
{
	bestSpecie.GetOutputs(inputs.back(), outputs); //move perfect model
	for (std::size_t i = 0; i < models.back().polys.size() - 1; ++i)
		models.back().polys[i].Joint->SetMotorSpeed(static_cast<float>(outputs[i] - outputs[i + 2])*JUMPFORCE);
}

auto Representative::ModelManager::DrawSfModels(Ball &ball) -> void
{
	for (std::size_t i = 0; i < models.size(); ++i) 
		for (std::size_t j = 0; j < models[i].polys.size(); ++j) {
		models[i].polys[j].sfpolygon.setPosition(sf::Vector2f(models[i].polys[j].poly->GetPosition().x * SCALE,
			                                                  models[i].polys[j].poly->GetPosition().y * SCALE));
		models[i].polys[j].sfpolygon.setRotation(models[i].polys[j].poly->GetAngle()*RADTODEG);
	}
	ball.SfBall.setPosition(sf::Vector2f((ball.b2Ball->GetWorldCenter().x - ballRadius) * SCALE,
		                                 (ball.b2Ball->GetWorldCenter().y - ballRadius) * SCALE));
}

auto Representative::ModelManager::UpdateFitnesses(Genus &life, Ball & ball, b2Body *Ground, b2Fixture *GroundFix) -> void
{
	hasBeenTouched.resize(models.size());

	for (std::size_t i = 0; i < models.size()-1; ++i) {
		hasBeenTouched[i].resize(models[i].polys.size());

		for (std::size_t j = 0; j < models[i].polys.size(); j++) {
			bool overlap1 = b2TestOverlap(models[i].polys[j].polyFix->GetShape(), 0, ball.getBallFix()->GetShape(), 0,
				models[i].polys[j].poly->GetTransform(), ball.b2Ball->GetTransform());
			if (overlap1)
				hasBeenTouched[i][j] = true;
		}

		auto& heightAboveGround = models[i].polys[models[i].polys.size() / 2].poly->GetWorldCenter().y;
		//if (25 - heightAboveGround > 4.5f && i < life.Species.size() && models[i].polys[models[i].polys.size() / 2].poly->GetLinearVelocity().y)
		//	life.Species[i].AddFitness(pow(29.5f - heightAboveGround, 1.35f));

		bool overlap2 = b2TestOverlap(models[i].polys[0].polyFix->GetShape(), 0, GroundFix->GetShape(), 0,
			models[i].polys[0].poly->GetTransform(), Ground->GetTransform());
		bool overlap3 = b2TestOverlap(models[i].polys[1].polyFix->GetShape(), 0, GroundFix->GetShape(), 0,
			models[i].polys[1].poly->GetTransform(), Ground->GetTransform());
		bool overlap4 = b2TestOverlap(models[i].polys[2].polyFix->GetShape(), 0, GroundFix->GetShape(), 0,
			models[i].polys[2].poly->GetTransform(), Ground->GetTransform());
		if(!overlap2 && !overlap3 && !overlap4)
			life.Species[i].AddFitness(pow(std::max(0.0f, 28.0f-heightAboveGround), 4));
	}
}

auto Representative::ModelManager::MoveToInitialState(b2World* newWorld) -> void
{
	SetWorld(newWorld);
	models.clear();
	ToProduceModels();
	StagnantTimer.clear();
	hasBeenTouched.clear();
	/*
	for (std::size_t i = 0; i < models.size(); ++i) {
		for (std::size_t j = 0; j < models[i].polys.size(); ++j) {
			models[i].polys[j].poly->SetTransform(models[i].GetSpawnPoint(), 0.0f);
			models[i].polys[j].poly->SetAngularVelocity(0.0f);
			models[i].polys[j].poly->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			if (j + 1 != models[i].polys.size())
				models[i].polys[j].Joint->SetMotorSpeed(0.0f);
			hasBeenTouched[i][j] = false;
			StagnantTimer[i] = 0;
		}
	}
	*/
}

auto Representative::ModelManager::UpdateBallFitness(Genus &life) -> void
{
	auto didSpecieTouchedBall = [&](std::size_t &index){
		for (std::size_t i = 0U; i < hasBeenTouched[index].size(); ++i) {
			if (hasBeenTouched[index][i])
				return true;
		}
		return false;
	};

	for (std::size_t i = 0; i < life.Species.size(); i++) {
		if (!didSpecieTouchedBall(i)) {
			life.Species[i].AddFitness(35);
			life.Species[i].MultiplicateFitness(2);
			touchedCounter++;
	//		std::cout << "BALL HASN'T BEEN TOUCHED!!!!\n";
		}
	}
	hasBeenTouched.clear();
}

auto Representative::ModelManager::PunishStagnantModels(Genus & life) -> void
{
	/*
	if (StagnantTimer.empty())
		StagnantTimer.resize(models.size());
	for (std::size_t i = 0U; i < models.size()-1; ++i) {
		if (!abs(models[i].polys[models[i].polys.size() / 2].poly->GetLinearVelocity().y))
			StagnantTimer[i]++;
		else
			StagnantTimer[i] = 0;
		if (StagnantTimer[i] >= 575) {
			life.Species[i].SetFitness(0);
			StagnantTimer[i] = 0;
			//std::cout << "phew";
		}
	}
	*/
}

auto Representative::ModelManager::ToProduceModels() -> void
{
	for (std::size_t i = 0; i < size-1; i++)
		AddNewModel();
	AddPerfectModel();
}

auto Representative::ModelManager::AddNewModel() -> void
{
	models.push_back(Model(coordinates.size(), SpawnPoint, coordinates));
	models.back().SetWorld(world);
	models.back().SetCategoryBits(categoryBits[models.size() - 1]);
	models.back().ToBorn();
}

auto Representative::ModelManager::AddPerfectModel() -> void
{
	models.push_back(Model(coordinates.size(), SpawnPoint, coordinates, true));
	models.back().SetWorld(world);
	models.back().SetCategoryBits(categoryBits[models.size() - 1]);
	models.back().ToBorn();
}
