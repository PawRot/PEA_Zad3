#include <iostream>
#include "../data/fileOperator.h"
#include "../data/dataGenerator.h"
#include "../algorithms/geneticOX.h"
#include "../algorithms/geneticPMX.h"

using std::vector, std::string, std::cout, std::cin, std::endl;


void showMenuOptions();

vector<vector<int>> loadFromFile(bool &dataLoaded);
vector<vector<int>> generateData(bool &dataLoaded);

void displayCurrentData(const vector<vector<int>>&data, bool dataLoaded);

void setPopulationSize(int &populationSize);

void setStopCriterion(int &stopCriterion, bool &stopCriterionSet);

void setMutationProbability(long double &mutationProbability);

void setCrossProbability(long double &crossProbability);

void selectCrossingMethod(int &crossingMethod);

void savePathToFile(const vector<int> &path, const bool &pathLoaded);

vector<int> loadPathFromFile(bool &pathLoaded);

void calculateCost(const vector<vector<int>> &testData, const vector<int> &path, const bool &dataLoaded, const bool &pathLoaded);

void startGeneticAlgorithm(const vector<vector<int>> &data, vector<int> &path, const int &stopCriterion, const int &populationSize, const long double &mutationProbability, const long double &crossProbability, const int &crossingMethod, const bool &dataLoaded, bool &pathLoaded);


const vector<string> crossingMethods = {"OX", "PMX"};

int main(int argc, char **argv)
{
    if (argc > 1 && std::string(argv[1]) == "testMode") {
        exit(0);
    }


    int choice = -1;
    string input;
    bool dataLoaded = false;
    bool pathLoaded = false;

    bool stopCriterionSet = false;
    int stopCriterion = 0;
    long double mutationProbability = 0.01;
    long double crossProbability = 0.8;
    int crossingMethod = 0;

    int populationSize = 1000;


    vector<vector<int>> data;
    vector<int> path;




    do {
        std::cout << "Data loaded: " << (dataLoaded ? "True" : "False") << std::endl;
        std::cout << "Current mutation probability = " << mutationProbability << std::endl;

        std::cout << "Current crossing probability = " << crossProbability << std::endl;
        std::cout << "Current crossing method = " << crossingMethods[crossingMethod] << std::endl;

        if (stopCriterionSet) {
            std::cout << "Current stop criterion = " << stopCriterion << " seconds" << std::endl;
        } else {
            std::cout << "Stop criterion not set" << std::endl;
        }

        cout << endl;

        showMenuOptions();
        std::cin >> input;

        try {
            choice = std::stoi(input);
        } catch (std::invalid_argument &e) {
            std::cout << "Invalid argument" << std::endl << std::endl;
            choice = -1;
        }


        switch (choice) {
            case 1:
                cout << endl;
                data = loadFromFile(dataLoaded);
                cout << endl;
                break;
            case 2:
                cout << endl;
                data = generateData(dataLoaded);
                cout << endl;
                break;
            case 3:
                cout << endl;
                displayCurrentData(data, dataLoaded);
                cout << endl;
                break;
            case 4:
                cout << endl;
                setStopCriterion(stopCriterion, stopCriterionSet);
                cout << endl;
                break;
            case 5:
                cout << endl;
                setPopulationSize(populationSize);
                cout << endl;
                break;
            case 6:
                cout << endl;
                startGeneticAlgorithm(data, path, stopCriterion, populationSize, mutationProbability, crossProbability, crossingMethod, dataLoaded, pathLoaded);
                cout << endl;
                break;
            case 7:
                cout << endl;
                setMutationProbability(mutationProbability);
                cout << endl;
                break;
            case 8:
                cout << endl;
                setCrossProbability(crossProbability);
                cout << endl;
                break;
            case 9:
                cout << endl;
                selectCrossingMethod(crossingMethod);
                cout << endl;
                break;
            case 10:
                cout << endl;
                savePathToFile(path, pathLoaded);
                cout << endl;
                break;
            case 11:
                cout << endl;
                path = loadPathFromFile(pathLoaded);
                cout << endl;
                break;
            case 12:
                cout << endl;
                calculateCost(data, path, dataLoaded, pathLoaded);
                cout << endl;
                break;
            default:
                break;
        }

    } while (choice != 0);
}

void showMenuOptions() {
    cout << "1.  Load data from file" << endl;
    cout << "2.  Generate data" << endl;
    cout << "3.  Display current data" << endl;
    cout << "4.  Set stop criterion" << endl;
    cout << "5.  Set population size" << endl;
    cout << "6.  Start genetic algorithm" << endl;
    cout << "7.  Set mutation probability" << endl;
    cout << "8.  Set crossing probability" << endl;
    cout << "9.  Select crossing method" << endl;
    cout << "10. Save path to file" << endl;
    cout << "11. Load data from file" << endl;
    cout << "12. Calculate path cost" << endl;
    cout << "0.  Exit" << endl;
}

vector<vector<int>> loadFromFile(bool &dataLoaded) {
    std::cout << "Enter file path: ";
    string filePath;
    //    std::cin >> filePath;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore newline character if present
    std::getline(std::cin, filePath); // use getline to get whole line with spaces

    std::cout << "Loading data from file: " << filePath << std::endl;
    // auto data = fileOperator::loadDataFromFile(filePath);
    auto data = fileOperator::loadXMLDataFromFile(filePath);
    if (!data.empty() || !data[0].empty()) {
        std::cout << "Data loaded successfully" << std::endl;
        dataLoaded = true;
        return data;
    } else {
        std::cout << "Data not loaded" << std::endl;
        dataLoaded = false;
        return {};
    }

}

vector<vector<int>> generateData(bool &dataLoaded) {
    std::cout << "Enter number of cities: ";
    string input;
    std::cin >> input;
    unsigned int numberOfCities;
    try {
        numberOfCities = std::stoi(input);
    } catch (std::invalid_argument &e) {
        std::cout << "Invalid argument" << std::endl;
        dataLoaded = false;
        return {};
    }

    if (numberOfCities < 2){
        std::cout << "Number of cities must be greater than 1" << std::endl;
        dataLoaded = false;
        return {};
    }

    std::cout << "Enter minimum distance between cities: ";
    unsigned int minimumDistance;
    std::cin >> input;

    try {
        minimumDistance = std::stoi(input);
    } catch (std::invalid_argument &e) {
        std::cout << "Invalid argument" << std::endl;
        dataLoaded = false;
        return {};
    }

    std::cout << "Enter maximum distance between cities: ";
    unsigned int maximumDistance;
    std::cin >> input;

    try {
        maximumDistance = std::stoi(input);
    } catch (std::invalid_argument &e) {
        std::cout << "Invalid argument" << std::endl;
        dataLoaded = false;
        return {};
    }
    std::cout << "Generating test data" << std::endl;
    auto data = dataGenerator::generateTestData(numberOfCities, maximumDistance, minimumDistance);
    if (!data.empty()) {
        std::cout << "Data generated successfully" << std::endl;
        dataLoaded = true;
        return data;
    } else {
        std::cout << "Data not generated" << std::endl;
        dataLoaded = false;
        return {};
    }

}

void displayCurrentData(const vector<vector<int>>&data, const bool dataLoaded) {
    if (!dataLoaded) {
        cout << "Data not loaded" << endl;
        return;
    }
    const int numberOfCities = static_cast<int>(data.size());
    std::cout << "Current number of cities: " << numberOfCities << std::endl;
    std::cout << "Current test data matrix: " << std::endl;
    for (int i = 0; i < numberOfCities; ++i) {
        for (int j = 0; j < numberOfCities; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

void setStopCriterion(int &stopCriterion,bool &stopCriterionSet) {
    std::cout << "Enter stop criterion in seconds: ";
    string input;
    std::cin >> input;
    int tempStopCriterion;
    try {
        tempStopCriterion = std::stoi(input);
    } catch (std::invalid_argument &e) {
        std::cout << "Invalid argument" << std::endl;
        stopCriterionSet = false;
        return;
    }

    if (tempStopCriterion < 1) {
        std::cout << "Stop criterion must be greater than 0" << std::endl;
        stopCriterionSet = false;
        return;
    }

    stopCriterion = tempStopCriterion;
    std::cout << "Stop criterion set to: " << stopCriterion << std::endl;
    stopCriterionSet = true;
}

void setPopulationSize(int &populationSize) {
    std::cout << "Enter desired population size: ";
    string input;
    std::cin >> input;
    int tempSize;
    try {
        tempSize = std::stoi(input);
    } catch (std::invalid_argument &e) {
        std::cout << "Invalid argument" << std::endl;
        return;
    }

    populationSize = tempSize;
    std::cout << "Population size set to: " << populationSize << std::endl;
}


void setMutationProbability(long double &mutationProbability) {
    std::cout << "Enter mutation probability: ";
    string input;
    std::cin >> input;
    double tempMutationProbability;
    try {
        tempMutationProbability = std::stod(input);
    } catch (std::invalid_argument &e) {
        std::cout << "Invalid argument" << std::endl;
        return;
    }

    if (tempMutationProbability < 0 || tempMutationProbability > 1) {
        std::cout << "Mutation probability must be between 0 and 1" << std::endl;
        return;
    }

    mutationProbability = tempMutationProbability;
    std::cout << "Mutation probability set to: " << mutationProbability << std::endl;
}

void setCrossProbability(long double &crossProbability) {
    std::cout << "Enter crossing probability: ";
    string input;
    std::cin >> input;
    double tempCrossProbability;
    try {
        tempCrossProbability = std::stod(input);
    } catch (std::invalid_argument &e) {
        std::cout << "Invalid argument" << std::endl;
        return;
    }

    if (tempCrossProbability < 0 || tempCrossProbability > 1) {
        std::cout << "Crossing probability must be between 0 and 1" << std::endl;
        return;
    }

    crossProbability = tempCrossProbability;
    std::cout << "Crossing probability set to: " << crossProbability << std::endl;
}

void selectCrossingMethod(int &crossingMethod) {
    std::cout << "Select crossing method: " << std::endl;
    for(int i = 0; i < crossingMethods.size(); ++i){
        std::cout << i + 1 << ". " << crossingMethods[i] << std::endl;
    }
    string input;
    std::cin >> input;
    int tempCrossingMethod;
    try {
        tempCrossingMethod = std::stoi(input);
    } catch (std::invalid_argument &e) {
        std::cout << "Invalid argument" << std::endl;
        return;
    }

    if (tempCrossingMethod < 1 || tempCrossingMethod > crossingMethods.size()) {
        std::cout << "Invalid argument" << std::endl;
        return;
    }

    crossingMethod = tempCrossingMethod - 1;
    std::cout << "Crossing method set to: " << crossingMethod << std::endl;
}


void savePathToFile(const vector<int> &path, const bool &pathLoaded ) {
    if (!pathLoaded) {
        cout << "Path not loaded" << endl;
        return;
    }
    std::cout << "Enter file path with extension: ";
    string filePath;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, filePath);

    std::cout << "Saving path to file: " << filePath << std::endl;
    fileOperator::savePathToFile(filePath, path);
}

vector<int> loadPathFromFile(bool&pathLoaded) {
    std::cout << "Enter file path: ";
    string filePath;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, filePath);

    std::cout << "Loading data from file: " << filePath << std::endl;
    auto data = fileOperator::loadPathFromFile(filePath);
    if (!data.empty()) {
        std::cout << "Data loaded successfully" << std::endl;
        pathLoaded = true;
        return data;
    } else {
        std::cout << "Data not loaded" << std::endl;
        pathLoaded = false;
        return {};
    }
}

void calculateCost(const vector<vector<int>>&testData, const vector<int>&path, const bool &dataLoaded, const bool &pathLoaded) {

    if (!dataLoaded) {
        cout << "Data not loaded" << endl;
        return;
    } if (!pathLoaded) {
        cout << "Path not loaded" << endl;
        return;
    }


    int cost = 0;

    std::cout << "Path: ";
    for (const auto element : path){
        std::cout << element << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < path.size() - 1; ++i) {
        cost += testData[path[i]][path[i + 1]];
    }

    std::cout << "Cost of path: " << cost;
}

void startGeneticAlgorithm(const vector<vector<int>> &data, vector<int> &path, const int &stopCriterion, const int &populationSize, const long double &mutationProbability, const long double &crossProbability, const int &crossingMethod, const bool &dataLoaded, bool &pathLoaded) {

    cout << "Starting genetic algorithm" << endl << endl;

    if(!dataLoaded) {
        cout << "Data not loaded" << endl;
        return;
    }

    if (crossingMethod == 0) {
        cout << "OX crossing" << endl;
        geneticOX geneticOX(data, stopCriterion, populationSize, crossProbability, mutationProbability);
        // auto result = geneticOX.geneticAlgorithm();
        auto [pathCost, resultPath, timeElapsed] = geneticOX.geneticAlgorithm();
        path = resultPath ;
        cout << "Cost: " << pathCost << endl;
        cout << "Best path found after: " << std::chrono::duration_cast<std::chrono::seconds>(timeElapsed).count() << " s" << endl;
        pathLoaded = true;
    } else {
        cout << "PMX crossing" << endl;
        geneticPMX geneticPMX(data, stopCriterion, populationSize, crossProbability, mutationProbability);
        // auto result = geneticPMX.geneticAlgorithm();
        auto [pathCost, resultPath, timeElapsed] = geneticPMX.geneticAlgorithm();
        path = resultPath ;
        cout << "Cost: " << pathCost << endl;
        cout << "Best path found after: " << std::chrono::duration_cast<std::chrono::seconds>(timeElapsed).count() << " s" << endl;
        pathLoaded = true;
    }

}


