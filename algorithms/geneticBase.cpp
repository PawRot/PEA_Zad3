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

    tournamentSize = 5;

    populationCosts = std::vector<int>(populationSize);

    for (int i = 0; i < populationSize; i++) {
        std::vector<int> path;
        path.reserve(numberOfCities);
        for (int j = 0; j < numberOfCities; j++) {
            path.push_back(j);
        }
        std::random_device rd;
        std::mt19937 mt(rd());
        std::ranges::shuffle(path, mt);
        population.push_back(path);
    }

    // auto populationCosts = std::vector<int>(populationSize);
    for (const auto& path : population) { // calculate the costs of the paths in the initial population
        populationCosts.push_back(pathCost(path));
    }

    // select the best path in the initial population
    bestPath = population[std::ranges::min_element(populationCosts) - populationCosts.begin()]; // find the best path

    // save the best path and the time when it was found
    bestSolution = {pathCost(bestPath), bestPath, std::chrono::duration<float>::zero()};

    // save the best path and the time when it was found
    betterPathsAndTimes = {std::to_string(pathCost(bestPath)) + "," + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::get<2>(bestSolution)).count())};

}

std::tuple<int, std::vector<int>, std::chrono::duration<float>> genetic::geneticAlgorithm() {

    std::random_device rd;
    std::mt19937 mt(rd());


    std::chrono::duration<float> timeElapsed = std::chrono::duration<float>::zero();
    const auto start = std::chrono::steady_clock::now(); // start time

    while (std::chrono::duration_cast<std::chrono::seconds>(timeElapsed) <= std::chrono::seconds(stopCriterion)) {
        numberOfGenerations++;

        std::vector<std::vector<int>> newPopulation; // container for the new population


        // tournament selection
        for (int i = 0; i < populationSize; i++) {
            int currentWinnerCost = INT_MAX;
            int currentWinnerIndex = -1;
            std::vector<int> indexInTournament = {};

            for (int k = 0; k < tournamentSize; k++) {
                // std::random_device rd;
                // std::mt19937 mt(rd());
                std::uniform_int_distribution index(0, populationSize - 1);
                int randomIndex = index(mt);
                while (std::ranges::find(indexInTournament, randomIndex) != indexInTournament.end()) { // if the random index is already in the tournament, generate a new one
                    randomIndex = index(mt);
                }
                indexInTournament.push_back(randomIndex);

                if (populationCosts[randomIndex] < currentWinnerCost) {
                    currentWinnerCost = populationCosts[randomIndex];
                    currentWinnerIndex = randomIndex;
                }
            }
            newPopulation.push_back(population[currentWinnerIndex]);
        }

        population = newPopulation; // set the current population to parent pool

        newPopulation.clear(); // clear the container for the new population

        // crossover
        for (int i = 0; i < populationSize; i += 2) {
            std::uniform_int_distribution index(0, populationSize - 1);
            const int parent1Index = index(mt);
            int parent2Index;
            do {
                parent2Index = index(mt);
            } while (parent1Index == parent2Index); // parent1Index and parent2Index must be different
            if (std::uniform_real_distribution dist(0.0, 1.0); dist(mt) < crossoverProbability) { // if the crossover is to be performed
                auto [fst, snd] = crossing(population[parent1Index], population[parent2Index]);
                newPopulation.push_back(fst);
                newPopulation.push_back(snd);
            } else { // if the crossover is not to be performed
                newPopulation.push_back(population[parent1Index]);
                newPopulation.push_back(population[parent2Index]);
            }
        }

        if (populationSize % 2 != 0) { // if the population size is odd, add one random path to the new population
            std::uniform_int_distribution index(0, populationSize - 1);
            newPopulation.push_back(population[index(mt)]);
        }

        for (auto& path : newPopulation) { // mutate the paths
            if (std::uniform_real_distribution dist(0.0, 1.0); dist(mt) < mutationProbability) { // if the mutation is to be performed
                path = mutate(path);
            }
        }

        // Calculate the costs of the paths in the new population
        populationCosts.clear();
        for (const auto& path : newPopulation) {
            populationCosts.push_back(pathCost(path));
        }

        // calculate the best path in the new population
        const auto bestPathInNewPopulation = newPopulation[std::ranges::min_element(populationCosts) - populationCosts.begin()];

        if (const auto bestCostInNewPopulation = pathCost(bestPathInNewPopulation); bestCostInNewPopulation < std::get<0>(bestSolution)) { // if the best path in the new population is better than the best path found so far, save it
            bestSolution = {bestCostInNewPopulation, bestPathInNewPopulation, std::chrono::steady_clock::now() - start}; // save the best path
            // save the new best path cost and the time when it was found
            betterPathsAndTimes.push_back(std::to_string(bestCostInNewPopulation) + "," + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::get<2>(bestSolution)).count()));
            numberOfGenerationsWhenBestPathWasFound = numberOfGenerations; // save the number of generations when the best path was found
        }

        population = newPopulation; // set the current population to the new population (full replacement)


        timeElapsed = std::chrono::steady_clock::now() - start; // time elapsed from the start of the algorithm
    }

    // add starting city to the best path
    std::get<1>(bestSolution).push_back(std::get<1>(bestSolution)[0]);

    return bestSolution;

}

std::vector<int> genetic::mutate(const std::vector<int>& path) const {

    // reciprocal exchange mutation (swap)
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution index(0, numberOfCities - 1);
    const int swapIndex1 = index(mt);
    int swapIndex2;
    do {
        swapIndex2 = index(mt);
    } while (swapIndex1 == swapIndex2); // swapIndex1 and swapIndex2 must be different
    std::vector<int> mutatedPath = path;
    std::swap(mutatedPath[swapIndex1], mutatedPath[swapIndex2]); // swap two cities
    return mutatedPath;

    // inversion mutation
    // std::random_device rd;
    // std::mt19937 mt(rd());
    // std::uniform_int_distribution index(0, numberOfCities - 1);
    // const int swapIndex1 = index(mt);
    // int swapIndex2;
    // do {
    //     swapIndex2 = index(mt);
    // } while (swapIndex1 == swapIndex2); // swapIndex1 and swapIndex2 must be different
    // std::vector<int> mutatedPath = path;
    // if (swapIndex1 < swapIndex2) {
    //     std::reverse(mutatedPath.begin() + swapIndex1, mutatedPath.begin() + swapIndex2);
    // } else {
    //     std::reverse(mutatedPath.begin() + swapIndex2, mutatedPath.begin() + swapIndex1);
    // }
    // return mutatedPath;

}


int genetic::pathCost(const std::vector<int>&testedPath) const {
    int cost = 0;
    for (int i = 0; i < numberOfCities - 1; i++) {
        cost += matrix[testedPath[i]][testedPath[i + 1]];
    }
    cost += matrix[testedPath[numberOfCities - 1]][testedPath[0]]; // Return to the starting city
    return cost;
}
