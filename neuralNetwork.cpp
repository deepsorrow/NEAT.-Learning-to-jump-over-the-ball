#include "neuralNetwork.h"
//#define _in 


Phenotype::NeuralNet::NeuralNet(const std::size_t &inputCount, const std::size_t &outputCount)
{

	genome.CreateLife(inputCount, outputCount);

	genome.SetConnections();
	connections = genome.GetConnections();

	BuildNeuralNetworkFromGenes();
}

Phenotype::NeuralNet::NeuralNet(const Genotype::Genome &newgenome)
{
	genome = newgenome;

	genome.SetConnections();
	connections = genome.GetConnections();

	BuildNeuralNetworkFromGenes();
}

auto Phenotype::NeuralNet::provideInputs(const std::vector<double>& newInputVals) -> void
{
	inputVals = newInputVals;

	neurons.clear();
	neurons.resize(genome.GetHighestIndex());

	for (int i = 0; i < inputVals.size(); i++)
		neurons[i].SetOutputVal(inputVals[i]);
}

auto Phenotype::NeuralNet::getResults(std::vector<double>& outputValues) -> void
{
	FeedForward();

	for (size_t i = inputVals.size(), j = 0; j < outputValues.size(); i++, j++)
		outputValues[j] = neurons[i].GetOutputVal();

	outputVals = outputValues;
}

auto Phenotype::NeuralNet::BuildNeuralNetworkFromGenes() -> void
{
	auto genes = genome.GetGenes(); 

	weights.resize(genome.GetHighestIndex());
	numberOfConnections.resize(genome.GetHighestIndex());

	for (std::size_t i = 0; i < genes.size(); i++) {
		weights[genes[i].GetIn()].resize(genome.GetHighestIndex());
		
		if (genes[i].GetMode() != false) {
			weights[genes[i].GetIn()][genes[i].GetOut()] = genes[i].GetWeight();
			numberOfConnections[genes[i].GetOut()]++;
		}
	}
}

auto Phenotype::NeuralNet::FeedForward() -> void
{
	for (std::size_t i = 0; i < neurons.size(); i++) {
		for (std::size_t j = 0; j < connections[i].size(); j++) {
			auto connectedNeuron = connections[i][j];
			auto sum = neurons[connectedNeuron].GetOutputVal() + neurons[i].GetOutputVal() * weights[i][connectedNeuron];
			neurons[connectedNeuron].arrivedSignalsCount += 1;

			if (neurons[connectedNeuron].arrivedSignalsCount == numberOfConnections[connectedNeuron]) {
				sum = tanh(sum);
			}
			neurons[connectedNeuron].SetOutputVal(sum);
		}
	}
}
