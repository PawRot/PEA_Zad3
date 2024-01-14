//
// Created by Michał Zychowicz on 11/01/2024.
//

#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <chrono>
#include <random>
#include <algorithm>



class genetic {
    std::vector<std::vector<int>> matrix; // data matrix
    std::vector<int> bestPath; // current best path
    int numberOfCities; // number of cities
    int populationSize; // size of the population
    int stopCriterion; // stop criterion in seconds
    int tournamentSize = 5; // size of the tournament
    long double crossoverProbability; // probability of crossover
    long double mutationProbability; // probability of mutation
    int numberOfGenerations = 0; // number of generations

    std::vector<std::vector<int>> population; // current population
    std::vector<int> populationCosts; // costs of the paths in the population

    std::tuple<int, std::vector<int>, std::chrono::duration<float>> bestSolution

    std::vector<std::string> betterPathsAndTimes; // vector of better paths and times when they were found

    [[nodiscard]] int pathCost(const std::vector<int>& testedPath) const; // calculates the curent path cost

protected:
    genetic(const std::vector<std::vector<int>> &matrix, int stopCriterion, int populationSize, long double crossoverProbability, long double mutationProbability);
    ~genetic() = default;

    virtual void crossing(int parent1, int parent2, int child1, int child2) = 0; // virtual method for crossing, will be implemented in the derived classes



public:


    // int - cost, vector - path, duration - time of the algorithm
    std::tuple<int, std::vector<int>, std::chrono::duration<float>> geneticAlgorithm(); // runs the algorithm

    [[nodiscard]] auto getBetterPathsAndTimes() const {
        return betterPathsAndTimes;
    }

    [[nodiscard]] int getNumberOfGenerations() const {
        return numberOfGenerations;
    }

};



#endif //GENETIC_H
