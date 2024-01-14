//
// Created by Michał Zychowicz on 14/01/2024.
//

#ifndef GENETICOX_H
#define GENETICOX_H

#include "geneticBase.h"



class geneticOX final : public genetic{

public:
    ~geneticOX() = default;
    geneticOX(const std::vector<std::vector<int>> &matrix, int stopCriterion, int populationSize,
              long double crossoverProbability, long double mutationProbability);

    std::pair<std::vector<int>, std::vector<int>> crossing(std::vector<int> parent1, std::vector<int> parent2) override;
};



#endif //GENETICOX_H
