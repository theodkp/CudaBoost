#include <vector>
#include <iostream>
#include "regressor.hpp"
#include "reg_tree.hpp"
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <cmath>

/// MSE HELPER
static float calculate_mse(const std::vector<float>& predictions, const std::vector<float>& targets) {
    float sum_squared_error = 0.0f;
    for (size_t i = 0; i < predictions.size(); ++i) {
        float error = predictions[i] - targets[i];
        sum_squared_error += error * error;
    }
    return sum_squared_error / predictions.size();
}

// ------------------------------------------------------------

Regressor::Regressor(int n_estimators, int max_depth, float learning_rate, std::string device, float initial_prediction)
    : n_estimators(n_estimators), max_depth(max_depth), learning_rate(learning_rate),
      device(std::move(device)), initial_prediction(initial_prediction) {
}

/// @brief Fitting the regressor to our data
/// @param X 
/// @param y 
void Regressor::fit(const std::vector<std::vector<float>>& X, const std::vector<float>& y) {
    std::cout << "Fitting GBM Regressor with parameters: " << std::endl;
    std::cout << "  n_estimators: " << n_estimators << std::endl;
    std::cout << "  max_depth: " << max_depth << std::endl;
    std::cout << "  learning_rate: " << learning_rate << std::endl;
    std::cout << "  device: " << device << std::endl;
    
    initial_prediction = std::accumulate(y.begin(), y.end(), 0.0f) / y.size();
    
    trees.clear();
    
    trees.reserve(n_estimators);
    
    std::vector<float> current_preds(y.size(), initial_prediction);
    
    float current_mse = calculate_mse(current_preds, y);
    float best_mse = current_mse;
    int best_iteration = 0;
    
    std::cout << "Initial MSE: " << std::fixed << std::setprecision(4) << current_mse << std::endl;
    
    const int patience = 5; 
    int no_improvement_count = 0;
    
    for (int i = 0; i < n_estimators; i++) {
        std::vector<float> residuals(y.size());
        for (size_t j = 0; j < y.size(); j++) {
            residuals[j] = y[j] - current_preds[j];
        }
        
        trees.emplace_back(max_depth);
        
        RegTree& tree = trees.back();
        
        tree.fit(X, residuals);
        
        std::vector<float> tree_preds = tree.predict(X);
        
        for (size_t j = 0; j < current_preds.size(); ++j) {
            float update = learning_rate * tree_preds[j];
            update = std::max(std::min(update, 10.0f), -10.0f);
            current_preds[j] += update;
        }
        
        current_mse = calculate_mse(current_preds, y);
        std::cout << "Tree " << (i+1) << "/" << n_estimators << " - MSE: " 
                  << std::fixed << std::setprecision(4) << current_mse << std::endl;
        
        
        /// EARLY STOPPING

        if (current_mse < best_mse) {
            best_mse = current_mse;
            best_iteration = i;
            no_improvement_count = 0;
        } else {
            no_improvement_count++;
        }
        
        if (no_improvement_count >= patience) {
            std::cout << "Early stopping at iteration " << (i+1) << std::endl;
            
            if (i > best_iteration) {
                trees.resize(best_iteration + 1);
                std::cout << "Keeping only the first " << (best_iteration + 1) << " trees." << std::endl;
            }
            break;
        }
                
    }
    
    std::cout << " best MSE: " << std::fixed << std::setprecision(4) << best_mse << std::endl;
}

/// @brief Making a prediction
/// @param X 
/// @return 
std::vector<float> Regressor::predict(const std::vector<std::vector<float>>& X) const {
    std::vector<float> predictions(X.size(), initial_prediction);
    
    for (const auto& tree : trees) {
        std::vector<float> tree_preds = tree.predict(X);
        
        for (size_t i = 0; i < predictions.size(); ++i) {
            predictions[i] += learning_rate * tree_preds[i];
        }
    }
    
    return predictions;
}
