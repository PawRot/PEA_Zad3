//
// Created by Michał Zychowicz on 14/01/2024.
//

#ifndef GENETICPMX_H
#define GENETICPMX_H

#include "geneticBase.h"
#include <unordered_map>



class geneticPMX final : public genetic{
public:
    ~geneticPMX() = default;
    geneticPMX(const std::vector<std::vector<int>> &matrix, int stopCriterion, int populationSize,
              long double crossoverProbability, long double mutationProbability);

    std::pair<std::vector<int>, std::vector<int>> crossing(std::vector<int> parent1, std::vector<int> parent2) override;

};



#endif //GENETICPMX_H
