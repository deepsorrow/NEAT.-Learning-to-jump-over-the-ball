#include "Gene.h"
#include "InnovationCacher.h"

Genotype::gene::gene(std::size_t InnovationNumber)
{
	auto Info = InnovationCacher::GetGeneInfoByInnovationNumber(InnovationNumber);
	in = Info.first;
	out = Info.second;
	weight = 0;
}

Genotype::gene::gene(const std::size_t &newIn, const std::size_t &newOut)
{
	in = newIn;
	out = newOut;
	weight = Genotype::gene::GetRandomWeight();
	enabled = true;
}

auto Genotype::gene::operator==(const gene & other) const -> bool
{
	 if (in == other.GetIn() && out == other.GetOut())
		return true;
	else
		return false;
}

auto Genotype::gene::GetRandomWeight() -> double const
{
	std::random_device r;                                         // 1
	std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() }; // 2
	std::mt19937 eng(seed);                                       // 3
	std::uniform_real_distribution<double> urd(0.0, 1.0);

	auto b = urd(eng);
	return b;
}

auto Genotype::gene::CorrectWeight() -> double const
{
	std::random_device r;                                         // 1
	std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() }; // 2
	std::mt19937 eng(seed);                                       // 3
	std::uniform_real_distribution<double> urd(0.6, 1.4);

	auto b = urd(eng);
	return b;
}
