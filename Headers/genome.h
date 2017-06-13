#pragma once
#include "gene.h"
#include "random.h"
#include <algorithm>
#include <deque>

#define Connection std::vector<std::size_t>

namespace Genotype
{
	class Genome
	{
	public:
		Genome() = default;
		explicit Genome(const std::deque<gene> &newgenes, const std::size_t newhighestIndex,
			const std::size_t &inputCount, const std::size_t &outputCount);

		auto UpdateGenes(const std::deque<gene> &newgenes) -> void const { genes = newgenes; }
		auto CreateLife(const std::size_t &inputCount, const std::size_t &outputCount) -> void;
		auto Mutate() -> void;

		auto SetHighestIndex(const std::size_t &highestInd) const -> void;
		auto SetConnections() -> void;
		auto GetHighestIndex() const -> std::size_t;
		auto GetNumberOfInputs()const -> std::size_t  {return inputs; }
		auto GetNumberOfOutputs() const -> std::size_t ;
		auto GetConnections() -> std::vector<Connection>;
		auto GetGenes() const -> std::deque<gene> { return genes; }
		auto IsConnectionFree(const std::size_t &newIn, const std::size_t &newOut) -> const bool;
		auto InsertGene(Genotype::gene &newGene) -> void;
		auto BreedWith(const Genotype::Genome &otherGenome) -> Genome;
		auto SetGenes(std::deque<gene> &newGenes) -> void { genes = newGenes; };
		auto SortGenesByInputs() -> void;
		auto SortGenesByInputs(std::deque<gene> &_genes) -> void;
		
	private:
		std::deque<gene> genes;
		mutable std::size_t highestIndex = 0;
		std::size_t inputs;
		std::size_t outputs;
		std::size_t hidden = 0;
		std::vector<Connection> existedConnections;
		mutable std::vector<Connection> existedGenes;
		auto AddHiddenNode(bool IsItSecondNode = false) -> void;
		auto AlterWeights() -> void;
		auto AddConnection() -> void;
		auto AlterGeneMode() -> void;
		auto IsConnectionsFilledUp() -> bool;
		auto IsInputNode(const std::size_t &value) const -> bool;
		auto IsOutputNode(const std::size_t &value) const -> bool;
		auto DidWeConnectedToOutputNeuron(const std::size_t &newIn) -> bool;
		auto ShouldBeSorted(const std::deque<gene> &genes, const std::size_t &I) const -> bool;
		auto GeneAreCompatible(const gene &partnerGene) const -> bool;
		auto SortByHistoricalMarkings() -> void;
		auto FindGeneByInnovationNumber(std::size_t index) const -> long long;

	};

}
