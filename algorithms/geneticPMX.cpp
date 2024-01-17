//
// Created by Michał Zychowicz on 14/01/2024.
//

#include "geneticPMX.h"

geneticPMX::geneticPMX(const std::vector<std::vector<int>>&matrix, const int stopCriterion, const int populationSize,
                       const long double crossoverProbability, const long double mutationProbability) : genetic(
    matrix, stopCriterion,
    populationSize,
    crossoverProbability,
    mutationProbability) {

}


std::pair<std::vector<int>, std::vector<int>> geneticPMX::crossing(const std::vector<int> parent1, const std::vector<int> parent2) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, numberOfCities - 1);

    // select random range
    int rangeStart = dist(mt);
    int rangeEnd;
    do {
        rangeEnd = dist(mt);
    }
    while (rangeStart == rangeEnd);
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
    for (int i = 0; i < numberOfCities-1; ++i) { //TODO: Remove -1
        if (i >= rangeStart && i <= rangeEnd) {
            continue;
        }
        if (std::find(offspring1.begin(), offspring1.end(), parent2[i]) == offspring1.end()) {
            offspring1[i] = parent2[i];
        }

        if (std::find(offspring2.begin(), offspring2.end(), parent1[i]) == offspring2.end()) {
            offspring2[i] = parent1[i];
        }
    }



    // copy cities from range from parent2 to offspring1, and from parent1 to offspring2
    for(int i = 0, j = 0; i < parent2.size() && j < parent2.size(); ++i) {
        if (offspring1[i] != -1) {
            continue;
        }

        while (j < parent2.size()) {
            if (std::find(offspring1.begin(), offspring1.end(), j) != offspring1.end()) {
                j++;
                continue;
            }
            break;
        }

        offspring1[i] = j;
        j++;
    }

    for(int i = 0, j = 0; i < parent1.size() && j < parent1.size(); ++i) {
        if (offspring2[i] != -1) {
            continue;
        }

        while (j < parent1.size()) {
            if (std::find(offspring2.begin(), offspring2.end(), j) != offspring2.end()) {
                j++;
                continue;
            }
            break;
        }

        offspring2[i] = j;
        j++;
    }


    return {offspring1, offspring2};
}
