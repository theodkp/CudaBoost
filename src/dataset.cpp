#include "dataset.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

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

    size_t numColumns = dataset.featureNames.size();
    std::vector<std::unordered_map<std::string, int>> categoryMappings(numColumns);
    std::vector<int> categoryIdCounters(numColumns, 0);

    // Getting data
    while (std::getline(iFile, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<float> row;
        row.reserve(numColumns);

        size_t colIndex = 0;
        while (std::getline(ss, cell, ',')) {
            // Strip spaces
            cell.erase(cell.begin(), std::find_if(cell.begin(), cell.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
            cell.erase(std::find_if(cell.rbegin(), cell.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(), cell.end());

            // Strip quotes
            if (!cell.empty() && cell.front() == '"' && cell.back() == '"') {
                cell = cell.substr(1, cell.size() - 2);
            }

            // Try to convert to float
            try {
                float val = std::stof(cell);
                row.push_back(val);
            } catch (const std::invalid_argument&) {
                // categorical data
                if (!categoryMappings[colIndex].count(cell)) {
                    categoryMappings[colIndex][cell] = categoryIdCounters[colIndex]++;
                }
                float categoryId = static_cast<float>(categoryMappings[colIndex][cell]);
                row.push_back(categoryId);
            }

            colIndex++;
        }

        if (row.size() != dataset.featureNames.size()) {
            throw std::runtime_error("Incomplete Row on line: " + line);
        }

        dataset.data.push_back(row);
    }

    iFile.close();
    return dataset;
}
