#include "specie.h"

Specie::Specie(const std::size_t & inpCount, const std::size_t & outCount)
{
	nInputs = inpCount;
	nOutputs = outCount;
	Mind = Phenotype::NeuralNet(nInputs, nOutputs);
	DNK = Mind.getGenome();
	Fitness = 0;
}

Specie::Specie(const Genotype::Genome & genome)
{
	nInputs = genome.GetNumberOfInputs();
	nOutputs = genome.GetNumberOfOutputs();
	DNK = genome;
	Mind = Phenotype::NeuralNet(DNK);
	Fitness = 0;
}

auto Specie::GetFitness() const -> double
{
	return Fitness;
}

auto Specie::GetOutputs(const std::vector<double>& inputs, std::vector<double>& outputs) -> void
{
	Mind.provideInputs(inputs);
	Mind.getResults(outputs);
}
