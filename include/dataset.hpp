#ifndef DATASET_HPP
#define DATASET_HPP

#include <string>
#include <vector>

struct Dataset {
    std::vector<std::string> featureNames;
    std::vector<std::vector<float>> data;
};

Dataset loadCSV(const std::string& filename);

#endif
