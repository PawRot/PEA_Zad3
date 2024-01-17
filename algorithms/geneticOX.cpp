//
// Created by Michał Zychowicz on 14/01/2024.
//

#include "geneticOX.h"

geneticOX::geneticOX(const std::vector<std::vector<int>> &matrix, const int stopCriterion, const int populationSize,
                     const long double crossoverProbability, const long double mutationProbability) : genetic(matrix, stopCriterion,
                                                                                                              populationSize,
                                                                                                              crossoverProbability,
                                                                                                              mutationProbability){}

std::pair<std::vector<int>, std::vector<int>> geneticOX::crossing(const std::vector<int> parent1, const std::vector<int> parent2) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, numberOfCities - 1);

    // select random range
    int rangeStart = dist(mt);
    int rangeEnd;
    do {
        rangeEnd = dist(mt);
    } while (rangeStart == rangeEnd);
    if (rangeStart > rangeEnd) {
        std::swap(rangeStart, rangeEnd);
    }

    // Create offspring with the genes in the selected range from their respective parent
    auto offspring1 = std::vector<int>(numberOfCities, -1);
    auto offspring2 = std::vector<int>(numberOfCities, -1);
    // copy the selected range from parent1 to offspring1, and from parent2 to offspring2. The rest is filled with -1
    std::copy(parent1.begin() + rangeStart, parent1.begin() + rangeEnd + 1, offspring1.begin() + rangeStart);
    std::copy(parent2.begin() + rangeStart, parent2.begin() + rangeEnd + 1, offspring2.begin() + rangeStart);

    // copy cities outside of range from parent2 to offspring1, and from parent1 to offspring2
    for(int parentIndex = (rangeEnd+1) % numberOfCities, childIndex = (rangeEnd+1) % numberOfCities; childIndex != rangeStart; childIndex = (childIndex + 1 ) % numberOfCities) {

        while (std::find(offspring1.begin(), offspring1.end(), parent2[parentIndex % numberOfCities]) != offspring1.end()) {
            parentIndex = (parentIndex + 1) % numberOfCities;
        }

        offspring1[childIndex] = parent2[parentIndex];

    }

    for(int parentIndex = (rangeEnd+1) % numberOfCities, childIndex = (rangeEnd+1) % numberOfCities; childIndex != rangeStart; childIndex = (childIndex + 1 ) % numberOfCities) {

        while (std::find(offspring2.begin(), offspring2.end(), parent1[parentIndex % numberOfCities]) != offspring2.end()) {
            parentIndex = (parentIndex + 1) % numberOfCities;
        }

        offspring2[childIndex] = parent1[parentIndex];

    }


    return {offspring1, offspring2};
}
