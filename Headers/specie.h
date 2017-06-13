#pragma once
#include "neuralNetwork.h"

class Specie
{
public:
	explicit Specie(const std::size_t &inpCount, const std::size_t &outCount);

	explicit Specie(const Genotype::Genome &genome);
	Specie() = default;

	//auto operator=(Specie &a) -> void { Mind = a.Mind; DNK = a.DNK; Fitness = a.Fitness; }
	auto SetFitness(const double &newFit) -> void { Fitness = newFit; }
	auto GetFitness() const -> double;
	auto AddFitness(double value) -> void { Fitness += value; }
	auto MultiplicateFitness(double value) -> void { Fitness *= value; }
	auto GetOutputs(const std::vector<double> &inputs, std::vector<double> &outputs) -> void;
	auto getGenome() const -> const Genotype::Genome{ return DNK; }
	auto setGenome(const Genotype::Genome &newGenome) -> void { DNK = newGenome; }
	auto BreedWith(const Specie& partner) -> const Specie { return Specie(DNK.BreedWith(partner.getGenome())); }

private:
	double Fitness = 0;
	std::size_t nInputs, nOutputs;
	Phenotype::NeuralNet Mind;
	Genotype::Genome DNK;
};
