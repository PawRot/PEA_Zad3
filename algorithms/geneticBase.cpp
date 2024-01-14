//
// Created by Michał Zychowicz on 11/01/2024.
//

#include "geneticBase.h"


genetic::genetic(const std::vector<std::vector<int>>& matrix, const int stopCriterion, const int populationSize,
                 const long double crossoverProbability, const long double mutationProbability) {
    this->matrix = matrix;
    this->stopCriterion = stopCriterion;
    this->populationSize = populationSize;
    this->crossoverProbability = crossoverProbability;
    this->mutationProbability = mutationProbability;
    numberOfCities = static_cast<int>(matrix.size());

    for (int i = 0; i < populationSize; i++) {
        std::vector<int> path;
        path.reserve(numberOfCities);
        for (int j = 0; j < numberOfCities; j++) {
            path.push_back(j);
        }
        std::random_device rd;
        std::mt19937 mt(rd());
        std::shuffle(path.begin(), path.end(), mt);
        population.push_back(path);
    }

    auto populationCosts = std::vector<int>(populationSize);
    for (const auto& path : population) { // calculate the costs of the paths in the initial population
        populationCosts.push_back(pathCost(path));
    }

    bestPath = population[std::ranges::min_element(populationCosts) - populationCosts.begin()]; // find the best path

    bestSolution = {pathCost(bestPath), bestPath, std::chrono::duration<float>::zero()};

}

std::tuple<int, std::vector<int>, std::chrono::duration<float>> genetic::geneticAlgorithm() {

    std::tuple<int, std::vector<int>, std::chrono::duration<float>> bestSolution = {INT_MAX, {}, std::chrono::duration<float>::zero()};

    std::chrono::duration<float> timeElapsed = std::chrono::duration<float>::zero();
    const auto start = std::chrono::steady_clock::now(); // start time

    while (std::chrono::duration_cast<std::chrono::seconds>(timeElapsed) <= std::chrono::seconds(stopCriterion)) {

        std::vector<std::vector<int>> newPopulation; // container for the new population

        populationCosts.clear();
        // Selection for crossover
        for (const auto& path : population) { // calculate the costs of the paths in the population
            populationCosts.push_back(pathCost(path));
        }

        // tournament selection
        for (int i = 0; i < populationSize; i++) {
            int currentWinnerCost = INT_MAX;
            int currentWinnerIndex = -1;

            for (int k = 0; k < tournamentSize; k++) {
                std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_int_distribution index(0, populationSize - 1);
                const int randomIndex = index(mt);
                if (populationCosts[randomIndex] < currentWinnerCost) {
                    currentWinnerCost = populationCosts[randomIndex];
                    currentWinnerIndex = randomIndex;
                }
            }
            newPopulation.push_back(population[currentWinnerIndex]);
        }

        // crossover
        for (int i = 0; i < populationSize; i += 2) {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> dist(0.0, 1.0);
            if (dist(mt) < crossoverProbability) { // if the crossover is to be performed
                std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_int_distribution index(0, numberOfCities - 1);
                const int randomIndex = index(mt);
                std::vector<int> child1;
                std::vector<int> child2;
                child1.reserve(numberOfCities);
                child2.reserve(numberOfCities);
                crossing(i, i + 1, child1, child2, randomIndex); // perform the crossover
                newPopulation[i] = child1;
                newPopulation[i + 1] = child2;
            }
        }



        timeElapsed = std::chrono::steady_clock::now() - start; // time elapsed from the start of the algorithm
    }

    return bestSolution;

}

int genetic::pathCost(const std::vector<int>&testedPath) const {
    int cost = 0;
    for (int i = 0; i < numberOfCities - 1; i++) {
        cost += matrix[testedPath[i]][testedPath[i + 1]];
    }
    cost += matrix[testedPath[numberOfCities - 1]][testedPath[0]]; // Return to the starting city
    return cost;
}
