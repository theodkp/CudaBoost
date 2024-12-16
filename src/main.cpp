#include <iostream>
#include "dataset.hpp"

int main() {
    try {
        Dataset data = loadCSV("../data/iris.csv");

        std::cout << "Dataset Loaded" << "\n";

        for (int i = 0; i <data.featureNames.size(); i++){
            std::cout << data.featureNames[i] << "\n";
        }


    } catch (const std::exception &ex) {
        std::cerr << "Error:"<< ex.what() << "\n";
    }

    return 0;
}
