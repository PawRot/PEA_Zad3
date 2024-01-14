//
// Created by Michał Zychowicz on 14/01/2024.
//

#include "geneticOX.h"

geneticOX::geneticOX(const std::vector<std::vector<int>> &matrix, const int stopCriterion, const int populationSize,
                     const long double crossoverProbability, const long double mutationProbability) : genetic(matrix, stopCriterion,
                                                                                                              populationSize,
                                                                                                              crossoverProbability,
                                                                                                              mutationProbability){}

std::pair<std::vector<int>, std::vector<int>> geneticOX::crossing(std::vector<int> parent1, std::vector<int> parent2) {
    return {parent1, parent2};
}
