#include "InnovationCacher.h"

std::size_t InnovationCacher::nextInnovationNumber = 0;
std::vector<Genotype::gene> InnovationCacher::genesCache;
/*
auto InnovationCacher::AssignInnovationNumbers(Genotype::Genome g) -> void
{
	auto tempGenes = g.GetGenes();
	for (std::size_t i = 0U; i < tempGenes.size(); ++i)
		AssignInnovationNumber(tempGenes[i]);
	g.SetGenes(tempGenes);
}
*/
auto InnovationCacher::AssignInnovationNumber(Genotype::gene & g) -> void
{
	auto index = FindThisGeneInCache(g);
	if (index == -1) { //not found
		g.setInnovationNumber(nextInnovationNumber++);
		genesCache.push_back(g);
	}
	else
		g.setInnovationNumber(index);

	return;
}

auto InnovationCacher::FindThisGeneInCache(Genotype::gene & g) -> long long
{
	auto it = std::find(genesCache.begin(), genesCache.end(), g);

	if(it != genesCache.end())
		return (it - genesCache.begin()); //index in 'genes' vector
	else
		return -1;
}

auto InnovationCacher::GetGeneInfoByInnovationNumber(std::size_t index) -> std::pair<std::size_t, std::size_t>
{
	std::pair<std::size_t, std::size_t> geneInfo;
	geneInfo.first = genesCache[index].GetIn();
	geneInfo.second = genesCache[index].GetOut();

	return geneInfo;
}
