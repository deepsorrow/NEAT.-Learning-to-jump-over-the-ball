#pragma once
#include "Gene.h"
class InnovationCacher {

public:
//	InnovationCacher(Genotype::Genome &newGenome) { AssignInnovationNumbers(newGenome); }
	InnovationCacher() = default;

	//static auto AssignInnovationNumbers(Genotype::Genome g) -> void;
	static auto AssignInnovationNumber(Genotype::gene &g) -> void;
	static auto FindThisGeneInCache(Genotype::gene &g) -> long long;
	static auto GetGeneInfoByInnovationNumber(std::size_t index) -> std::pair<std::size_t, std::size_t>;
private:
	static std::vector<Genotype::gene> genesCache;
	static std::size_t nextInnovationNumber;
};