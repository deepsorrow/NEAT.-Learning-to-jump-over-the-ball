#pragma once
#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
#include <limits>
#include <algorithm>
#include <cmath>
#include <memory>
#include "genome.h"
#include "InnovationCacher.h"
#define Connection std::vector<std::size_t>

namespace Phenotype
{
	class NeuralNet
	{
	public:
		explicit NeuralNet(const std::size_t &inputCount, const std::size_t &outputCount);
		explicit NeuralNet(const Genotype::Genome &newgenome);
		explicit NeuralNet() = default;
		auto provideInputs (const std::vector<double> &newInputVals) -> void;  // Сообщает нейросети входные данные
		auto getResults(std::vector<double> &outputVals) -> void; // Возвращает выходные данные
		auto getGenome() const -> const Genotype::Genome {  return genome;  } // Возвращает генотип
		auto setGenome(const Genotype::Genome &newGenome) -> void { genome = newGenome; }

	private:
		auto BuildNeuralNetworkFromGenes() -> void; // Создать нейронную сеть из генов
		auto FeedForward() -> void; // Метод прямого распространения

		std::vector<Connection> connections; // Соединения между нейронами
		std::vector< std::vector<double> > weights; // Весовые коэффициенты каждого соединения
		std::vector<Phenotype::Neuron> neurons; // Нейроны
		std::vector<double> inputVals;  // Вектор, хранящий входные данные
		std::vector<double> outputVals; // Вектор, хранящий выходные данные
		std::vector<std::size_t> numberOfConnections;  // Вектор, хранящий кол-во входящий соединений для каждого нейрона
		Genotype::Genome genome;  // Генотип нейросети
	};
}
