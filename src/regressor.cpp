#include <vector>
#include <iostream>
#include <regressor.hpp>

Regressor::Regressor(int n_estimators, int max_depth, float learning_rate, int n_bins, std::string device)
    : n_estimators(n_estimators), max_depth(max_depth), learning_rate(learning_rate),
      n_bins(n_bins), device(std::move(device)) {
}

void Regressor::fit(const std::vector<std::vector<float>>& X, const std::vector<float>& y) {
    std::cout << "Fitting the model" << std::endl;
    for (int i = 0; i < n_estimators; i++) {
        std::cout << "Building tree " << i << " with depth " << max_depth << std::endl;
        float update = learning_rate * 1.0;
        std::cout << "Using " << n_bins << " bins on " << device << std::endl;
    }
}

std::vector<float> Regressor::predict(const std::vector<std::vector<float>>& X) {
    std::cout << "Predicting for " << X.size() << " samples" << std::endl;
    return std::vector<float>(X.size(), 0.0f);
}
