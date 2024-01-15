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


std::pair<std::vector<int>, std::vector<int>> geneticPMX::crossing(std::vector<int> parent1, std::vector<int> parent2) {
    // select random range
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, numberOfCities - 1);
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
    // copy the selected range from parent1 to offspring1
    std::copy(parent1.begin() + rangeStart, parent1.begin() + rangeEnd + 1, offspring1.begin() + rangeStart);
    // copy the selected range from parent2 to offspring2
    std::copy(parent2.begin() + rangeStart, parent2.begin() + rangeEnd + 1, offspring2.begin() + rangeStart);


    // Insert genes that are in one parent's range but not in the other
    for (int i = rangeStart; i <= rangeEnd; i++) {
        if (std::find(offspring1.begin() + rangeStart, offspring1.begin() + rangeEnd + 1, parent2[i]) == offspring1.begin() + rangeEnd + 1) {
            const auto index = static_cast<int>(std::distance(parent2.begin(), std::find(parent2.begin(), parent2.end(), parent1[i])));
            if (offspring1[index] == -1) {
                offspring1[index] = parent2[i];
            }
            else {
                auto index2 = static_cast<int>(std::distance(parent2.begin(),std::find(parent2.begin(), parent2.end(), parent1[index])));
                while (offspring1[index2] != -1) {
                     index2 = static_cast<int>(std::distance(parent2.begin(),std::find(parent2.begin(), parent2.end(), parent1[index2])));
                }
                offspring1[index2] = parent2[i];
            }
        }

        if (std::find(offspring2.begin() + rangeStart, offspring2.begin() + rangeEnd + 1, parent1[i]) == offspring2.begin() + rangeEnd + 1) {
            const auto index = static_cast<int>(std::distance(parent1.begin(), std::find(parent1.begin(), parent1.end(), parent2[i])));
            if (offspring2[index] == -1) {
                offspring2[index] = parent1[i];
            }
            else {
                auto index2 = static_cast<int>(std::distance(parent1.begin(),std::find(parent1.begin(), parent1.end(), parent2[index])));
                while (offspring1[index2] != -1) {
                    index2 = static_cast<int>(std::distance(parent1.begin(),std::find(parent1.begin(), parent1.end(), parent2[index2])));
                }
                offspring2[index2] = parent1[i];
            }
        }
    }

    // Copy the remaining genes from parent2 to offspring1 and parent1 to offspring2
    for (int i = 0; i < rangeStart; i++) {
        if (offspring1[i] == -1) {
            offspring1[i] = parent2[i];
        }
        if (offspring2[i] == -1) {
            offspring2[i] = parent1[i];
        }
    }
    for (int i = rangeEnd + 1; i < numberOfCities; i++) {
        if (offspring1[i] == -1) {
            offspring1[i] = parent2[i];
        }
        if (offspring2[i] == -1) {
            offspring2[i] = parent1[i];
        }
    }
    return {offspring1, offspring2};
}
