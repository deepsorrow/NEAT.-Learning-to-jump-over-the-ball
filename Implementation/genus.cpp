#include "Genus.h"
#include "random.h"

std::random_device Random::randomDevice;
std::mt19937 Random::engine;

Genus::Genus()
{
	Species.resize(SizeOfPopulation);
}

Genus::Genus(const std::size_t & Size, const std::size_t & inputVals, const std::size_t & outputVals, Specie & first, Specie & second)
	: SizeOfPopulation(Size), inputs(inputVals), outputs(outputVals)
{
	MakeNewSpeciesFromDifferentGenuses(first, second);
	ancestors.push_back(Specie(inputs, outputs)); //to have first element of anchestors(leader)
}

auto Genus::BringToLife() -> void
{
	MakeNewRandomSpecie(SizeOfPopulation);
}

auto Genus::MakeNewRandomSpecie(const std::size_t &Amount) -> void
{
	for (std::size_t i = 0; i < Amount; i++)
		Species.push_back(Specie(inputs, outputs));
}

auto Genus::MakeNewSpecieFromASingleFather() -> void
{
	for (std::size_t i = 0U; i < Species.size(); ++i) {
		auto child = Species.back().BreedWith(Species.back());
		Species.push_back(child);
	}
}

auto Genus::MakeNewSpeciesFromDifferentGenuses(Specie &first, Specie &second) -> void
{
	first.SetFitness(0);
	second.SetFitness(0);
	Species.push_back(first);
	Species.push_back(second);

	for (std::size_t i = 1U; i < SizeOfPopulation-1; ++i) {
		auto child = Species[i].BreedWith(Species[i-1]);
		Species.push_back(child);
	}
}

auto Genus::EvaluateLastSpecie() -> void
{
	for (std::size_t i = 0; i < Species.size() - 1; i++)
		if (Species[i].GetFitness() < Species[i+1].GetFitness())
			std::swap(Species[i], Species[i+1]);
}

auto Genus::EvaluateAnchestors() -> void
{
	for (std::size_t i = 0; i < ancestors.size(); ++i)
		for (std::size_t j = 0; j < ancestors.size() - i - 1; ++j)
			if (ancestors[j].GetFitness() < ancestors[j + 1].GetFitness()){
				auto temp = ancestors[j];
				ancestors[j] = ancestors[j + 1];
				ancestors[j + 1] = temp;
			}
}

auto Genus::DropLosersFromAncestors() -> void
{
	ancestors.resize(ancestorCapacity);
}

auto Genus::MutateSpecies() -> void
{
	for (std::size_t i = 0; i<SizeOfPopulation; i+=rand()%2+1) {
		Genotype::Genome genome = Species[i].getGenome();
		genome.Mutate();

		Species[i] = Specie(genome);
	}
}

auto Genus::BreedSpecies() -> void
{
	for (std::size_t i = 0U; i < Species.size(); i++)
		ancestors.push_back(Species[i]);

	Species.clear();
	EvaluateAnchestors();
	DropLosersFromAncestors();

	for (std::size_t i = 0U; i < SizeOfPopulation; ++i) {
		auto mother = GetSpecieToBreed();
		auto father = GetSpecieToBreed();
		auto child = father.BreedWith(mother);
		if (child.GetFitness() != 0)
			throw std::runtime_error("Child's fitness is not 0");

		Species.push_back(child);
	}
}

auto Genus::Evolve() -> void
{
	BreedSpecies();
	MutateSpecies();
}

auto Genus::GetSpecieToBreed() -> Specie &
{
	double SummaryFitness = 0;
	for (std::size_t i = 0U; i < ancestors.size(); ++i) {
		SummaryFitness += ancestors[i].GetFitness();
	}

	while (true)
	{
		for (std::size_t i = 0U; i < ancestors.size(); ++i) {
			if (Random::DidChanceOccure(ancestors[i].GetFitness() / SummaryFitness)) {
				return ancestors[i];
			}
		}
	}
}
