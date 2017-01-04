#include "geneticalgorithm.h"



GeneticAlgorhitm::GeneticAlgorhitm(Net &net)
{
  BestIndex = 0;
  index = 0;
  BestFitness = 0;
  m_layersData.push_back(vector<Layer>());
  m_layersData[0] = net.m_layers;
}

vector<Layer> GeneticAlgorhitm::makeNewGeneration(vector<unsigned> &topology, Net &net, double &fitness)
{
    CrossoverCount = 35 - rand()%36;
    if(fitness > BestFitness)
    {
        BestFitness = fitness;
        BestIndex = index;
    }

    //Crossover(Mutation):
    m_layersData.push_back(vector<Layer>());
    if(index != BestIndex)
       m_layersData[index] = m_layersData[BestIndex];
    else
       m_layersData[index] = net.m_layers;

    for(size_t m_layer=0; m_layer < net.m_layers.size(); m_layer++){
        for(size_t neuronNum=0; neuronNum < net.m_layers[m_layer].size(); neuronNum++){

            unsigned numOutputs = m_layer == topology.size() - 1 ? 0 : topology[m_layer + 1];

             for(size_t connectionNumb=0; connectionNumb < numOutputs; connectionNumb+=rand()%4){
               m_layersData[index][m_layer][neuronNum].m_outputWeights[connectionNumb].weight = randomWeight();

               if(CrossoverCount != 0) CrossoverCount --;
               else goto outOfCycles;
              }

        }
    }
    outOfCycles:
    index++;
    return m_layersData[index-1];
}

void GeneticAlgorhitm::moveBody(b2Body *bodyA, b2Body *bodyB, b2Body *bodyC, vector<double> &outputVals)
{
    if(outputVals[0] >= 0.7)
        bodyA->ApplyAngularImpulse(outputVals[0]*RotateConst,false);
    else if(outputVals[0] >= 0.4)
        bodyA->ApplyAngularImpulse(-outputVals[0]*RotateConst,false);

    if(outputVals[1] >= 0.7)
        bodyB->ApplyAngularImpulse(outputVals[1]*RotateConst,false);
    else if(outputVals[1] >= 0.4)
        bodyB->ApplyAngularImpulse(-outputVals[1]*RotateConst,false);

    if(outputVals[2] >= 0.7)
        bodyC->ApplyAngularImpulse(outputVals[2]*RotateConst,false);
    else if(outputVals[2] >= 0.4)
        bodyC->ApplyAngularImpulse(-outputVals[2]*RotateConst,false);
}

double GeneticAlgorhitm::randomWeight()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 0.3);

    return dis(gen);
}
