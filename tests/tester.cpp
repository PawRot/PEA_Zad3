//
// Created by Michał Zychowicz on 17/01/2024.
//

#include "tester.h"

void tester::run_tests(const std::string& crossover_type, const std::string& stop_criterion, const std::string& population_size, const std::string& filePath) {
    int bestKnownCost = INT_MAX;
    std::vector<int> bestPath;
    std::vector<std::string> betterPathsAndTimes = {};

    const int stopCriterion = std::stoi(stop_criterion); // seconds
    const int populationSize = std::stoi(population_size);
    std::string fileNameTest = crossover_type + "_" + population_size + "_" + filePath + "_test.csv";
    std::string fileNameBest = crossover_type + "_" + population_size + "_" + filePath + "_best.csv";
    std::string fileNamePath = crossover_type + "_" + population_size + "_" + filePath + "_path.txt";
    const auto data = fileOperator::loadXMLDataFromFile(filePath);
    if (filePath == "ftv47.xml") {
        bestKnownCost = 1776;
    } else if (filePath == "ftv170.xml") {
        bestKnownCost = 2755;
    } else if (filePath == "rbg403.xml") {
        bestKnownCost = 2465;
    } else {
        std::cout << "Wrong path" << std::endl;
        throw std::invalid_argument("Wrong path");
    }
    if (crossover_type == "0") {
        std::cout << "Testing file: " << filePath << " | Crossover type: OX | Population size: " << populationSize << " | Stop criterion: " << stopCriterion << "s" << std::endl;
        for (int i = 0; i < 10; i++) {
            const auto genetic = new geneticOX(data, stopCriterion, populationSize, 0.8, 0.01);

            auto [cost, path, time] = genetic->geneticAlgorithm();
            auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
            const auto error = (static_cast<double>(cost) - static_cast<double>(bestKnownCost)) / static_cast<double>(bestKnownCost);
            int error_int = static_cast<int>(error * 100000); // 5 digits after comma
            fileOperator::saveResultFile(fileNameTest, {cost, time_ms, error_int});

            if (cost < bestKnownCost) {
                bestKnownCost = cost;
                bestPath = path;
                betterPathsAndTimes = genetic->getBetterPathsAndTimes();
            }

        }
    }else if (crossover_type == "1") {
        std::cout << "Testing file: " << filePath << " | Crossover type: OX | Population size: " << populationSize << " | Stop criterion: " << stopCriterion << "s" << std::endl;

        for (int i = 0; i < 10; i++) {
            auto genetic = new geneticPMX(data, stopCriterion, populationSize, 0.8, 0.01);

            auto [cost, path, time] = genetic->geneticAlgorithm();
            auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
            const auto error = (static_cast<double>(cost) - static_cast<double>(bestKnownCost)) / static_cast<double>(bestKnownCost);
            int error_int = static_cast<int>(error * 100000); // 5 digits after comma
            fileOperator::saveResultFile(fileNameTest, {cost, time_ms, error_int});

            if (cost < bestKnownCost) {
                bestKnownCost = cost;
                bestPath = path;
                betterPathsAndTimes = genetic->getBetterPathsAndTimes();
            }

        }
    }

    fileOperator::savePathToFile(fileNamePath, bestPath);
    fileOperator::saveEpochsToFile(fileNameBest, betterPathsAndTimes);
}
