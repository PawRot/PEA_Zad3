
#ifndef TESTER_H
#define TESTER_H
#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include "../data/fileOperator.h"
#include "../algorithms/geneticOX.h"
#include "../algorithms/geneticPMX.h"


class tester {
public:
    // crossover_type: 0 - OX, 1 - PMX | Stop_criterion: seconds
    void static run_tests(const std::string& crossover_type, const std::string& stop_criterion, const std::string& population_size, const std::string& filePath);

};



#endif //TESTER_H
