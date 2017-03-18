#pragma once
#include <iostream>
#include <vector>
#include <memory>

namespace Phenotype
{
	class Neuron
	{
	public:
		explicit Neuron() = default;

		auto SetOutputVal(const double &value) -> void { outputVal = value; }
		auto GetOutputVal() const -> double { return outputVal; }
		std::size_t arrivedSignalsCount = 0;
	private:
		std::size_t connections;
		double outputVal = 0;
   };
}