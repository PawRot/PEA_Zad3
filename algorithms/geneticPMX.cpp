//
// Created by Michał Zychowicz on 14/01/2024.
//

#include "geneticPMX.h"
#include <iostream>

geneticPMX::geneticPMX(const std::vector<std::vector<int>>&matrix, const int stopCriterion, const int populationSize,
                       const long double crossoverProbability, const long double mutationProbability) : genetic(
    matrix, stopCriterion,
    populationSize,
    crossoverProbability,
    mutationProbability) {
}

// std::pair<std::vector<int>, std::vector<int>> geneticPMX::crossing(std::vector<int> parent1, std::vector<int> parent2) {
//     // select random range
//     std::random_device rd;
//     std::mt19937 mt(rd());
//     std::uniform_int_distribution<int> dist(0, numberOfCities - 1);
//     int rangeStart = dist(mt);
//     int rangeEnd = dist(mt);
//     if (rangeStart > rangeEnd) {
//         std::swap(rangeStart, rangeEnd);
//     }
//
//
// }

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

    // create a map of the genes in the selected range
    // auto map1 = std::unordered_map<int, int>();
    // auto map2 = std::unordered_map<int, int>();
    // for (int i = rangeStart; i <= rangeEnd; i++) {
    //     map1[parent1[i]] = parent2[i];
    //     map2[parent2[i]] = parent1[i];
    // }
    std::cout << std::endl;

    // print key and value of the maps
    // for (const auto& [key, value] : map1) {
    // std::cout << key << " " << value << std::endl;
    // }

    // Insert genes that are in one parent's range but not in the other
    for (int i = rangeStart; i <= rangeEnd; i++) {
        if (std::find(offspring1.begin(), offspring1.end(), parent2[i]) == offspring1.end()) {
            const auto index = static_cast<int>(std::distance(parent2.begin(), std::find(parent2.begin(), parent2.end(), parent1[i])));
            if (offspring1[index] == -1) {
                offspring1[index] = parent2[i];
            }
            else {
                const auto index2 = static_cast<int>(std::distance(parent2.begin(),std::find(parent2.begin(), parent2.end(), parent1[index])));
                offspring1[index2] = parent2[i];
            }
        }
    }

    // // Fill the remaining genes without duplicating any in the selected range
    // for (int i = 0; i < numberOfCities; i++) {
    //     if (i < rangeStart || i > rangeEnd) {
    //         // If the offspring doesn't have the gene add it from the other parent
    //         if (std::find(offspring1.begin(), offspring1.end(), parent2[i]) == offspring1.end()) {
    //             offspring1[i] = parent2[i];
    //         }
    //         if (std::find(offspring2.begin(), offspring2.end(), parent1[i]) == offspring2.end()) {
    //             offspring2[i] = parent1[i];
    //         }
    //     }
    // }


    // Fill the remaining genes without duplicating any in the selected range

    // Rotate the offspring to match the parent's starting point
    // std::rotate(offspring1.begin(), std::find(offspring1.begin(), offspring1.end(), parent1[0]), offspring1.end());
    // std::rotate(offspring2.begin(), std::find(offspring2.begin(), offspring2.end(), parent2[0]), offspring2.end());

    return {offspring1, offspring2};
}
