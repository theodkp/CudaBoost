#include "dataset.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>


Dataset loadCSV(const std::string& filename) {
    std::ifstream iFile(filename);
    if (!iFile.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    Dataset dataset;
    
    // Getting header
    if (std::getline(iFile, line)) {
        std::stringstream ss(line);
        std::string columnName;
        while (std::getline(ss, columnName, ',')) {
            dataset.featureNames.push_back(columnName);
        }
    } else {
        throw std::runtime_error("File is empty: " + filename);
    }
    
    // Getting data
    while (std::getline(iFile, line)) {
        
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ',')) {
            try {
                row.push_back(cell); 
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Invalid data:" + cell);
            }
        }

        if (row.size() != dataset.featureNames.size()) {
            throw std::runtime_error("Incomplete Row on line:" + line);
        }

        dataset.data.push_back(row);
    }

    iFile.close();
    return dataset;
}
