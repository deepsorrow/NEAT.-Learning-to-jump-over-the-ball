#include "genusManager.h"

GenusManager::GenusManager(const std::size_t newsize, const std::size_t GenusSize, const std::vector<double> &inputVals,
	const std::vector<double> &outputVals) : size(newsize), inputValsCount(inputVals.size()), outputValsCount(outputVals.size())
	, initialGenusSize(GenusSize)
{
	for (std::size_t i = 0; i < size; ++i)
		AddNewRandomGenus();
}

auto GenusManager::SortGenuses() -> void
{
	for (std::size_t i = 0U; i < size; ++i)
		for (std::size_t j = 0U; j < size - i - 1; ++j)
			if (Genuses[j].GetFittestOrganism().GetFitness() < Genuses[j + 1].GetFittestOrganism().GetFitness()){
				auto temp = Genuses[j+1];
				Genuses[j + 1] = Genuses[j];
				Genuses[j] = temp;
			}
}

auto GenusManager::GetFittestGenus() -> Genus
{
	Genus BestGenus;
	for (auto& g : Genuses)
		if (g.GetFittestOrganism().GetFitness() > BestGenus.GetFittestOrganism().GetFitness())
			BestGenus = g;
	return BestGenus;
}

auto GenusManager::AddNewRandomGenus() -> void
{
	Genuses.push_back(Genus(initialGenusSize, inputValsCount, outputValsCount));
	Genuses.back().BringToLife();
}

auto GenusManager::SortGenusesAndPopWorst() -> void
{
	SortGenuses();
	Genuses.pop_back();
}

auto GenusManager::AddNewInterspecieGenus() -> void
{
	SortGenuses();

	auto first = GetGenusToMate().GetSpecieToBreed();
	auto second = GetGenusToMate().GetSpecieToBreed();
	if (Random::DidChanceOccure(0.5))
		Genuses.pop_back(); //pop worst
	Genuses.push_back(Genus(initialGenusSize, inputValsCount, outputValsCount, first, second));
}

auto GenusManager::GetGenusToMate() -> Genus
{
	double SummaryFitness = 0;
	for (std::size_t i = 0U; i < Genuses.size(); ++i) {
		SummaryFitness += Genuses[i].GetFittestOrganism().GetFitness();
	}

	while (true)
	{
		for (std::size_t i = 0U; i < Genuses[i].getAncestors().size(); ++i) {
			if (Random::DidChanceOccure(Genuses[i].GetFittestOrganism().GetFitness() / SummaryFitness)) {
				return Genuses[i];
			}
		}
	}
}
