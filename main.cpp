#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <stdlib.h>
#include <utility>
#include <algorithm>
#include "polygons.h"
#include "environment.h"
#include "geneticalgorithm.h"

const float radius=1.2f;
#define RADTODEG 57.295779513082320876f

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720, 60), "Neural Network");
    window.setFramerateLimit(60);

    std::vector<float> coordinates1(8);

    coordinates1[0] = 0.0f;
    coordinates1[1] = 0.0f;
    coordinates1[2] = 1.0f;
    coordinates1[3] = 2.0f;
    coordinates1[4] = 3.0f;
    coordinates1[5] = 2.0f;
    coordinates1[6] = 3.0f;
    coordinates1[7] = 0.0f;

    std::vector<float> coordinates2(8);

    coordinates2[0] = 0.0f;
    coordinates2[1] = 0.0f;
    coordinates2[2] = 1.0f;
    coordinates2[3] = 2.0f;
    coordinates2[4] = 2.0f;
    coordinates2[5] = 2.0f;
    coordinates2[6] = 2.0f;
    coordinates2[7] = 0.0f;

    std::vector<float> coordinates3(8);

    coordinates3[0] = 0.0f;
    coordinates3[1] = 0.0f;
    coordinates3[2] = 0.0f;
    coordinates3[3] = 2.0f;
    coordinates3[4] = 2.0f;
    coordinates3[5] = 2.0f;
    coordinates3[6] = 1.0f;
    coordinates3[7] = -1.0f;

    Environment env;
    Polygon polygon1, polygon2, polygon3;

    vector<unsigned> topology;
    topology.push_back(4);
    topology.push_back(6);
    topology.push_back(3);

    Net NN(topology);
    GeneticAlgorhitm GA = GeneticAlgorhitm(NN);

    vector<double> inputVals(4), outputVals(3);

    env.CreateB2bounds(*env.world);
    env.CreateSfbounds();
    env.CreateSfHeightLine();
    env.CreateSfMaxHeightLine();
    env.CreateSfDot();

    polygon1.CreateSfpolygon(coordinates1, sf::Color::Green, 125.0f);
    polygon2.CreateSfpolygon(coordinates2, sf::Color::Blue, 100.0f);
    polygon3.CreateSfpolygon(coordinates3, sf::Color::Red, 75.0f);

    b2Vec2 p1 = b2Vec2(10.0f,17.0f);
    b2Vec2 p2 = b2Vec2(13.0f,19.0f);
    b2Vec2 p3 = b2Vec2(15.0f,21.0f);

    polygon1.CreateB2polygon(*env.world, coordinates1, p1);
    polygon2.CreateB2polygon(*env.world, coordinates2, p2);
    polygon3.CreateB2polygon(*env.world, coordinates3, p3);

    polygon1.CreateRevJoint(*env.world, polygon1.poly, polygon2.poly, b2Vec2(-3.0f,-2.0f));
    polygon2.CreateRevJoint(*env.world, polygon2.poly, polygon3.poly, b2Vec2(-2.0f,-2.0f));

    double fitness = 0, maxHeight = 999, height = 0, maxFitness = 0;
    int iteration = 0, generation = 1, bestGeneration = 1;

    while(window.isOpen()){
        env.world->Step(1/60.0f, 8, 3);

        sf::Event event;
        while (window.pollEvent(event))  { if (event.type == sf::Event::Closed)  window.close();  }

        iteration++;
        height = polygon2.poly->GetWorldCenter().y;
        fitness = 25 - height;
        if(maxFitness < fitness)
        {
            maxFitness = fitness;
            bestGeneration = generation;
        }

        polygon1.sfpolygon->setPosition(sf::Vector2f(polygon1.poly->GetPosition().x * SCALE, polygon1.poly->GetPosition().y * SCALE));
        polygon2.sfpolygon->setPosition(sf::Vector2f(polygon2.poly->GetPosition().x * SCALE, polygon2.poly->GetPosition().y * SCALE));
        polygon3.sfpolygon->setPosition(sf::Vector2f(polygon3.poly->GetPosition().x * SCALE, polygon3.poly->GetPosition().y * SCALE));
        env.heightLine->setPosition(sf::Vector2f(0.0f, height * SCALE));
        env.MaxheightLine->setPosition(sf::Vector2f(0.0f, maxHeight * SCALE));
        env.Dot->setPosition(sf::Vector2f(polygon2.poly->GetWorldCenter().x * SCALE, polygon2.poly->GetWorldCenter().y * SCALE));

        polygon1.sfpolygon->setRotation(polygon1.poly->GetAngle()*RADTODEG);
        polygon2.sfpolygon->setRotation(polygon2.poly->GetAngle()*RADTODEG);
        polygon3.sfpolygon->setRotation(polygon3.poly->GetAngle()*RADTODEG);

        if(polygon2.poly->GetWorldCenter().y < maxHeight)
        {
            maxHeight = polygon2.poly->GetWorldCenter().y;
        }

        double k = polygon1.poly->GetAngle()*RADTODEG - 360 * ((int)(polygon1.poly->GetAngle()*RADTODEG/360));
        inputVals[0] = k;

        k = polygon2.poly->GetAngle()*RADTODEG - 360 * ((int)(polygon2.poly->GetAngle()*RADTODEG/360));
        inputVals[1] = k;

        k = polygon3.poly->GetAngle()*RADTODEG - 360 * ((int)(polygon3.poly->GetAngle()*RADTODEG/360));
        inputVals[2] = k;

        inputVals[3] = 25-height;

        NN.feedForward(inputVals);
        NN.getResults(outputVals);

        GA.moveBody(polygon1.poly, polygon2.poly, polygon3.poly, outputVals);

        if(iteration == 700)
        {
            NN.m_layers = GA.makeNewGeneration(topology, NN, maxFitness);
            generation++;
            iteration = 0;
            env.MoveToInitialState(polygon1.poly, polygon2.poly, polygon3.poly, p1, p2, p3);
        }

        env.getInfoString(polygon1.poly, polygon2.poly, polygon3.poly, env.BodyGround, inputVals, outputVals, fitness, iteration, generation, bestGeneration, maxFitness);

        env.KeyboardControl(window);

        window.draw(*env.text);
        window.draw(*env.groundsf);
        window.draw(*env.leftwall);
        window.draw(*env.rightwall);
        window.draw(*env.ceiling);
        window.draw(*env.heightLine);
        window.draw(*env.MaxheightLine);
        window.draw(*env.Dot);
        window.draw(*polygon1.sfpolygon);
        window.draw(*polygon2.sfpolygon);
        window.draw(*polygon3.sfpolygon);

        window.display();

        window.clear(sf::Color::White);
    }
}
