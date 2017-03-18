#include "Genome.h"
#include "InnovationCacher.h"

Genotype::Genome::Genome(const std::deque<gene>& newgenes, const std::size_t newhighestIndex, const std::size_t &inputCount, const std::size_t &outputCount)
{
	genes = newgenes;
	highestIndex = newhighestIndex;
	inputs = inputCount;
	outputs = outputCount;
	existedGenes.resize(highestIndex);
	SetConnections();
}

auto Genotype::Genome::CreateLife(const std::size_t &inputCount, const std::size_t &outputCount) -> void
{
	srand((unsigned)time(NULL)); //reset seed

	inputs = inputCount;
	outputs = outputCount;

	auto random = rand() % 101;
	for (size_t i = 0; i < outputCount; i++){
		for (size_t j = 0; j < inputCount; j++) {
			gene newGene = gene(j, i + inputCount);
			InsertGene(newGene);
		}
	}

	highestIndex = inputs + outputs + 1;
}

auto Genotype::Genome::SetHighestIndex(const std::size_t & highestInd) const -> void
{
	highestIndex = highestInd;
}

auto Genotype::Genome::GetHighestIndex() const ->  std::size_t
{
	return highestIndex;
}

auto Genotype::Genome::GetNumberOfOutputs() const -> std::size_t
{
	return outputs;
}

auto Genotype::Genome::SetConnections() -> void
{
	existedConnections.clear();
	existedConnections.resize(highestIndex);
	existedGenes.resize(highestIndex);

	for (std::size_t i = 0; i < genes.size(); i++) {
		existedGenes[genes[i].GetIn()].resize(highestIndex);
		existedGenes[genes[i].GetIn()][genes[i].GetOut()] = 1;
		if (genes[i].GetMode() != false) {
			existedConnections[genes[i].GetIn()].push_back(genes[i].GetOut());
		}
	}
}

auto Genotype::Genome::GetConnections() -> std::vector<Connection>
{
	return existedConnections;
}

auto Genotype::Genome::IsConnectionFree(const std::size_t &newIn, const std::size_t &newOut) -> const bool
{
	if (newIn != newOut) {
		for (std::size_t i = 0; i < existedConnections[newIn].size(); i++)
			if (existedConnections[newIn][i] == newOut)
				return false;
		for (std::size_t i = 0; i < existedConnections[newOut].size(); i++)
			if (existedConnections[newOut][i] == newIn)
				return false;
		return true;
	}

	else
		return false;
}

auto Genotype::Genome::InsertGene(Genotype::gene &newGene) -> void
{
	InnovationCacher::AssignInnovationNumber(newGene);
	genes.push_front(newGene);

	for (std::size_t i = 0; i < genes.size() - 1; i++){
		if (ShouldBeSorted(genes, i)) {
			auto temp = genes[i];
			genes[i] = genes[i + 1];
			genes[i + 1] = temp;
		}
		else
			return;
	}
}

auto Genotype::Genome::BreedWith(const Genotype::Genome &otherGenome) -> Genome
{
	auto _otherGenome = otherGenome;

	SortByHistoricalMarkings();
	_otherGenome.SortByHistoricalMarkings();

	auto localMaxInnovationNumber =
		std::max(otherGenome.GetGenes().back().getInnovationNumber(), genes.back().getInnovationNumber());

	std::deque<gene> _newGenes;

	for (std::size_t innNumber = 0U; innNumber  <= localMaxInnovationNumber; ++innNumber) {
		auto ind1 = FindGeneByInnovationNumber(innNumber);
		auto ind2 = _otherGenome.FindGeneByInnovationNumber(innNumber);
		auto _otherGenomeGenes = _otherGenome.GetGenes();
		gene offspringGene(innNumber);
		offspringGene.setInnovationNumber(innNumber);

		if (ind1 != -1 && ind2 != -1) { //if both genomes has this gene
			
			if (genes[ind1].GetMode() != _otherGenomeGenes[ind2].GetMode() && Random::DidChanceOccure(0.2)) //mode
				offspringGene.SetNewMode(true);
			else
				offspringGene.SetNewMode(genes[ind1].GetMode());

			if (Random::FlipACoin()) //weight
				offspringGene.SetWeight(genes[ind1].GetWeight());
			else
				offspringGene.SetWeight(_otherGenomeGenes[ind2].GetWeight());
		}
		else if (ind1 != -1 || ind2 != -1) {
			if (ind1 != -1) {
				offspringGene.SetNewMode(genes[ind1].GetMode());
				offspringGene.SetWeight(genes[ind1].GetMode());
			}
			else {
				offspringGene.SetNewMode(_otherGenomeGenes[ind2].GetMode());
				offspringGene.SetWeight(_otherGenomeGenes[ind2].GetMode());
			}
		}
		if(offspringGene.GetWeight() != 0) //if this gene was set up
			_newGenes.push_back(offspringGene);
	}
	auto maxHighestIndex = std::max(GetHighestIndex(), _otherGenome.GetHighestIndex());

	SortGenesByInputs(_newGenes);
	Genome offspringGenome(_newGenes, maxHighestIndex, inputs, outputs);

	return offspringGenome;
}

auto Genotype::Genome::SortGenesByInputs() -> void
{
	for (std::size_t i = 0; i < genes.size(); ++i)
		for (std::size_t j = 0; j < genes.size() - i - 1; ++j)
			if (genes[j].GetIn() > genes[j + 1].GetIn()) {
				auto temp = genes[j];
				genes[j] = genes[j + 1];
				genes[j + 1] = temp;
			}
}

auto Genotype::Genome::SortGenesByInputs(std::deque<gene>& _genes) -> void
{
	for (std::size_t i = 0; i < _genes.size(); ++i)
		for (std::size_t j = 0; j < _genes.size() - i - 1; ++j)
			if (_genes[j].GetIn() > _genes[j + 1].GetIn()) {
				auto temp = _genes[j];
				_genes[j] = _genes[j + 1];
				_genes[j + 1] = temp;
			}
}

auto Genotype::Genome::Mutate() -> void
{
	while (rand() % 100 <= 8)
			AddHiddenNode(); // Дополнительный узел

	while (rand() % 100 <= 5)
			AddConnection(); // Дополнительное соединение
			
	while (rand() % 100 <= 3)
			AlterGeneMode(); // Изменить состояние некоторых генов

			AlterWeights(); // Изменить весовые коэфф. некоторых генов
}

auto Genotype::Genome::AddHiddenNode(bool IsItSecondNode) -> void
{
	auto newIn = rand() % (highestIndex-1);
	auto newOut = highestIndex-1;

	if (IsItSecondNode) {
		std::swap(newIn, newOut);

		while ( IsInputNode(newOut) || genes.back().GetIn() == newOut)
			newOut = rand() % newIn;
	}
	else
		while ( IsOutputNode(newIn))
		newIn = rand() % newOut;

	gene newGene = gene(newIn, newOut);
	InsertGene(newGene);
	existedConnections.push_back( Connection() );
	existedGenes.push_back(Connection());

	existedConnections[newIn].push_back(newOut);

	existedGenes[newIn].resize(highestIndex);
	existedGenes[newIn][newOut] = 1;

	if(!IsItSecondNode)
		AddHiddenNode(true);
	else
	{
		highestIndex++;
		hidden+=2;
	}
}

auto Genotype::Genome::AlterWeights() -> void
{
	for (size_t i = 0U; i < genes.size(); i++){
		double weight;
		if (rand() % 100 <= 95)
			weight = (genes[i].GetWeight() * gene::CorrectWeight());
		else
			weight = (genes[i].GetWeight() * gene::GetRandomWeight());

		genes[i].SetWeight( weight );
	}
}

auto Genotype::Genome::AddConnection() -> void
{
	auto newIn = 0U, newOut = 0U, count = 0U;

	while ( count<45 && (!IsConnectionFree(newIn, newOut) || ( IsInputNode(newIn) && IsInputNode(newOut) )  || //if two connected node are both inputs
	 ( IsOutputNode(newIn) && IsOutputNode(newOut) )))  {										                    //...are both outputs
		newIn = rand() % (highestIndex-1);
		newOut = rand() % (highestIndex-1);
		count++;
	}
	if (count == 45) return; // if there's no free connections

	gene newGene = gene(newIn, newOut);
	InsertGene(newGene);
	existedConnections[newIn].push_back(newOut);
}

auto Genotype::Genome::AlterGeneMode() -> void
{
	for (std::size_t i = 0; i < genes.size(); i++) {
		if (rand() % 101 <= 5)
			genes[i].SetNewMode(); // Поменять состояние гена на противоположный
	}
}

auto Genotype::Genome::IsConnectionsFilledUp() -> bool
{
	for (std::size_t i = inputs; i < existedConnections.size(); i++){
		if (existedConnections[i].size() != (inputs + outputs + hidden))
			return false;
	}
	return true;
}

auto Genotype::Genome::IsInputNode(const std::size_t &value) const -> bool
{
	if (value < inputs)
		return true;
	else
		return false;
}

auto Genotype::Genome::IsOutputNode(const std::size_t &value) const -> bool
{
	if ((value >= inputs) && (value < (inputs + outputs) ) )
		return true;
	else
		return false;
}

auto Genotype::Genome::DidWeConnectedToOutputNeuron(const std::size_t &newIn) -> bool
{
	if (newIn >= inputs && newIn < (inputs + outputs))
		return true;
	else
		return false;
}

auto Genotype::Genome::ShouldBeSorted(const std::deque<gene>& genes, const std::size_t &I) const -> bool
{
	if (genes[I].GetIn() > genes[I + 1].GetIn())
		return true;
	else
		return false;
}

auto Genotype::Genome::GeneAreCompatible(const gene &partnerGene) const -> bool
{
	if (existedGenes[partnerGene.GetIn()].size() >= partnerGene.GetOut() || existedGenes[partnerGene.GetIn()][partnerGene.GetOut()] == 1)
		return false;

	if (existedGenes[partnerGene.GetOut()].size() >= partnerGene.GetIn() || existedGenes[partnerGene.GetOut()][partnerGene.GetIn()] == 1)
		return false;

	return true;
}

auto Genotype::Genome::SortByHistoricalMarkings() -> void
{
	for (std::size_t i = 0; i < genes.size(); ++i)
		for (std::size_t j = 0; j < genes.size() - i - 1; ++j)
			if (genes[j].getInnovationNumber() > genes[j+1].getInnovationNumber()){
				auto temp = genes[j];
				genes[j] = genes[j + 1];
				genes[j + 1] = temp;
			}
}

auto Genotype::Genome::FindGeneByInnovationNumber(std::size_t index) const -> long long
{
	if (index > genes.back().getInnovationNumber()) //assuming 'genes' are already sorted by historical markings
		return -1;

	for (std::size_t i = 0U; i < genes.size(); ++i) {
		if (genes[i].getInnovationNumber() == index)
			return i;
	}

	return -1;
}

