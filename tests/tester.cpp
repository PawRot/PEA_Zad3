
#include "tester.h"

void tester::run_tests(const std::string& crossover_type, const std::string& stop_criterion, const std::string& population_size, const std::string& filePath) {
    int bestKnownCost;
    std::vector<int> bestPath;
    int bestPathCost = INT_MAX;
    std::vector<std::string> betterPathsAndTimes = {};

    const int stopCriterion = std::stoi(stop_criterion); // seconds
    const int populationSize = std::stoi(population_size);
    std::string crossover_name;
    if (crossover_type == "0") {
        crossover_name = "OX";
    } else if (crossover_type == "1") {
        crossover_name = "PMX";
    } else {
        std::cout << "Wrong crossover type" << std::endl;
        throw std::invalid_argument("Wrong crossover type");
    }

    std::string fileName;
    if (filePath.find("ftv47.xml") != std::string::npos) {
        bestKnownCost = 1776;
        fileName = "ftv47";
    } else if (filePath.find("ftv170.xml") != std::string::npos) {
        bestKnownCost = 2755;
        fileName = "ftv170";
    } else if (filePath.find("rbg403.xml") != std::string::npos) {
        bestKnownCost = 2465;
        fileName = "rbg403";
    } else {
        std::cout << "Wrong path" << std::endl;
        throw std::invalid_argument("Wrong path");
    }

    std::string fileNameTest = crossover_name + "_" + population_size + "_" + fileName + "_test.csv";
    std::string fileNameBest = crossover_name + "_" + population_size + "_" + fileName + "_best.csv";
    std::string fileNamePath = crossover_name + "_" + population_size + "_" + fileName + "_path.txt";
    const auto data = fileOperator::loadXMLDataFromFile(filePath);

    if (crossover_type == "0") {
        std::cout << "Testing file: " << filePath << " | Crossover type: OX | Population size: " << populationSize << " | Stop criterion: " << stopCriterion << "s" << std::endl;
        for (int i = 0; i < 10; i++) {
            const auto genetic = new geneticOX(data, stopCriterion, populationSize, 0.8, 0.01);

            auto [cost, path, time] = genetic->geneticAlgorithm();
            auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
            const auto error = (static_cast<double>(cost) - static_cast<double>(bestKnownCost)) / static_cast<double>(bestKnownCost);
            int error_int = static_cast<int>(error * 100000); // 5 digits after comma
            fileOperator::saveResultFile(fileNameTest, {cost, time_ms, error_int});

            if (cost < bestPathCost) {
                bestPathCost = cost;
                bestPath = path;
                betterPathsAndTimes = genetic->getBetterPathsAndTimes();
            }

        }
    }else if (crossover_type == "1") {
        std::cout << "Testing file: " << filePath << " | Crossover type: PMX | Population size: " << populationSize << " | Stop criterion: " << stopCriterion << "s" << std::endl;

        for (int i = 0; i < 10; i++) {
            auto genetic = new geneticPMX(data, stopCriterion, populationSize, 0.8, 0.01);

            auto [cost, path, time] = genetic->geneticAlgorithm();
            auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
            const auto error = (static_cast<double>(cost) - static_cast<double>(bestKnownCost)) / static_cast<double>(bestKnownCost);
            int error_int = static_cast<int>(error * 100000); // 5 digits after comma
            fileOperator::saveResultFile(fileNameTest, {cost, time_ms, error_int});

            if (cost < bestPathCost) {
                bestPathCost = cost;
                bestPath = path;
                betterPathsAndTimes = genetic->getBetterPathsAndTimes();
            }

        }
    }
    fileOperator::savePathToFile(fileNamePath, bestPath);
    fileOperator::saveEpochsToFile(fileNameBest, betterPathsAndTimes);
}
