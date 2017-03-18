#pragma once
#include "specie.h"
#include <utility>
#include <algorithm>

class Genus {

public: 
	 explicit Genus(const std::size_t &Size, const std::size_t &inputVals, const std::size_t &outputVals)
		 : SizeOfPopulation(Size), inputs(inputVals), outputs(outputVals) {
		 ancestors.push_back(Specie(inputs, outputs));
	 };
     explicit Genus(const std::size_t &Size, const std::size_t &inputVals, const std::size_t &outputVals,
		 Specie &first, Specie &second);
	 explicit Genus();

	 auto operator=(Genus &a) -> void { ancestors = a.ancestors; Species = a.Species; }

	auto BringToLife() -> void;
	auto MakeNewRandomSpecie(const std::size_t &Amount = 1) -> void;
	auto MakeNewSpecieFromASingleFather() -> void;
	auto MakeNewSpeciesFromDifferentGenuses(Specie &first, Specie &second) -> void;
	auto GetFittestOrganism() const -> Specie { return ancestors[0];}
	auto EvaluateLastSpecie() -> void;
	auto EvaluateAnchestors() -> void;
	auto DropLosersFromAncestors() -> void;
	auto MutateSpecies() -> void;
	auto BreedSpecies() -> void;
	auto GetSpecieToBreed()->Specie&;
	auto getAncestors() -> std::vector<Specie> { return ancestors; }
	auto Evolve() -> void;
	std::vector<Specie> Species;

private:
	std::size_t inputs;
	std::size_t outputs;
	std::vector<Specie> ancestors;

	const std::size_t SizeOfPopulation = 14;
	const std::size_t ancestorCapacity = 175;
};