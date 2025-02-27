#include <vector>
#include <iostream>
#include <regressor.hpp>

Regressor::Regressor(int n_estimators, int max_depth, float learning_rate, int n_bins, std::string device) {
}

void Regressor::fit(const std::vector<std::vector<float>>& X, const std::vector<float>& y) {
    std::cout << "Fitting the model" << std::endl;
}
