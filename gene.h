#pragma once
#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
#include <limits>
#include <string>
#include <map>
#include <random>
#include <ctime>
#include "neuron.h"
#include "random.h"

namespace Genotype
{
	class gene
	{
	public:
		explicit gene() = default;
		explicit gene(std::size_t InnovationNumber);
		explicit gene(const std::size_t &newIn, const std::size_t &newOut);	

		auto operator==(const gene& other) const -> bool;

		static auto GetRandomWeight() -> double const;
		static auto CorrectWeight() -> double const;
		auto GetIn() const -> std::size_t { return in; }
		auto GetOut() const -> std::size_t { return out; }
		auto GetWeight() const -> double { return weight;  }
		auto SetWeight(const double &newWeight) { weight = newWeight; }
		auto SetNewMode() -> void { enabled = !enabled; }
		auto SetNewMode(bool mode) -> void { enabled = mode; }
		auto GetMode() const -> bool { return enabled; }

		auto setInnovationNumber(const std::size_t n) ->  void { innovation_number = n; }
		auto getInnovationNumber() const -> std::size_t { return innovation_number; }

	private:
		std::size_t in;
		std::size_t out;
		double weight;
		bool enabled;
		std::size_t innovation_number;
	};
}