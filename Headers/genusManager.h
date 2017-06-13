#pragma once
#include "genus.h"

class GenusManager {

public:
	explicit GenusManager(const std::size_t newsize, const std::size_t GenusSize, const std::vector<double> &inputVals,
		const std::vector<double> &outputVals);

	auto SortGenuses() -> void;
	auto GetFittestGenus() -> Genus;
	auto AddNewRandomGenus() -> void;
	auto SortGenusesAndPopWorst() -> void;
	auto AddNewInterspecieGenus() -> void;
	auto GetGenusesSize() -> std::size_t { return Genuses.size(); };
	auto GetGenusToMate() -> Genus;

	auto operator[](std::size_t index) const -> const Genus& { return Genuses[index]; }
	auto operator[](std::size_t index) -> Genus& { return Genuses[index]; }
private:

	const std::size_t size;
	std::vector<Genus> Genuses;
	const std::size_t inputValsCount;
	const std::size_t outputValsCount;
	const std::size_t initialGenusSize;
};
