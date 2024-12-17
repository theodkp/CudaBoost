#include <iostream>
#include "dataset.hpp"

int main() {
    try {
        Dataset data = loadCSV("../data/iris.csv");

        std::cout << "Dataset Loaded" << "\n";

        for (int i = 0; i <data.data.size(); i++){
            for (int j = 0; j < data.data[i].size(); j++){
                std::cout << data.data[i][j] << " ";
            }
            std::cout << "\n";
        }


    } catch (const std::exception &ex) {
        std::cerr << "Error:"<< ex.what() << "\n";
    }

    return 0;
}
