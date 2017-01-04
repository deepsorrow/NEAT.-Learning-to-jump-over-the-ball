#ifndef GENETICALGORHITM_H
#define GENETICALGORHITM_H
#include <vector>
#include "neuralnet.h"
#include "environment.h"
class GeneticAlgorhitm
{
public:
    GeneticAlgorhitm(Net &net);
    vector<Layer> makeNewGeneration(vector<unsigned> &topology, Net &net, double &fitness);
    void moveBody(b2Body *bodyA, b2Body *bodyB, b2Body *bodyC, vector<double> &outputVals);
    double BestFitness;


private:
   vector<Connection> weights;
   int index;
   int BestIndex;
   vector< vector<Layer> > m_layersData;
   const float RotateConst=0.9f;
   double randomWeight();
   int CrossoverCount;
};

#endif // GENETICALGORHITM_H
