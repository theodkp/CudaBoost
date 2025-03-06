#include "reg_tree.hpp"
#include <limits>
#include <algorithm>
#include <cmath>

RegTree::RegTree(int max_depth) : max_depth(max_depth) {
    root = nullptr;
}

void RegTree::fit(const std::vector<std::vector<float>>& X, const std::vector<float>& y){
    if (X.empty() || y.empty()) {
        std::cerr << "No data" << std::endl;
        return;
    }
    
    if (X.size() != y.size()) {
        std::cerr << "Error: X and y must have the same number of samples" << std::endl;
        return;
    }
    
    delete root;
    root = nullptr;
    
    root = _build_tree(X, y, 0);
    
    if (root == nullptr) {
        std::cerr << "Error: Failed to build tree" << std::endl;
    }
}

Node* RegTree::_build_tree(const std::vector<std::vector<float>>& X, const std::vector<float>& y, int depth){
    int sample_count = X.size();
    
    if (X.empty() || y.empty()) {
        std::cerr << "Error: Empty data at depth: " << depth << std::endl;
        return nullptr;
    }
    
    int feature_count = X[0].size();

    float mean_value = 0.0f;
    for (const auto& val : y) {
        mean_value += val;
    }
    mean_value /= y.size();

    if (depth >= max_depth || sample_count < 2){
        return new Node(mean_value);
    }

    auto [best_feature, best_threshold] = _best_split(X, y, feature_count);

    if (best_feature == -1){
        return new Node(mean_value);
    }

    std::vector<size_t> left_indices;
    std::vector<size_t> right_indices;
    
    for (size_t i = 0; i < sample_count; ++i) {
        if (X[i][best_feature] < best_threshold) {
            left_indices.push_back(i);
        } else {
            right_indices.push_back(i);
        }
    }
    
    if (left_indices.empty() || right_indices.empty()) {
        return new Node(mean_value);
    }

    auto extractRows = [](const std::vector<std::vector<float>>& matrix, const std::vector<size_t>& indices) {
        std::vector<std::vector<float>> result;
        result.reserve(indices.size());
        
        for (size_t idx : indices) {
            result.push_back(matrix[idx]);
        }
        
        return result;
    };

    auto extractElements = [](const std::vector<float>& vec, const std::vector<size_t>& indices) {
        std::vector<float> result;
        result.reserve(indices.size());
        
        for (size_t idx : indices) {
            result.push_back(vec[idx]);
        }
        
        return result;
    };
    
    std::vector<std::vector<float>> X_left = extractRows(X, left_indices);
    std::vector<float> y_left = extractElements(y, left_indices);
    
    std::vector<std::vector<float>> X_right = extractRows(X, right_indices);
    std::vector<float> y_right = extractElements(y, right_indices);
    
    Node* left_child = _build_tree(X_left, y_left, depth + 1);
    Node* right_child = _build_tree(X_right, y_right, depth + 1);
    
    if (left_child == nullptr || right_child == nullptr) {
        std::cerr << "Error: Failed to build child node at depth " << depth << std::endl;
        delete left_child;
        delete right_child;
        return new Node(mean_value);
    }
    
    return new Node(best_feature, best_threshold, -1, left_child, right_child);
}

std::pair<int, float> RegTree::_best_split(const std::vector<std::vector<float>>& X, const std::vector<float>& y, int feature_count){
    float best_mse = std::numeric_limits<float>::max();
    int best_feature = -1;
    float best_threshold = 0.0f;
    
    for (int feature = 0; feature < feature_count; ++feature) {
        std::vector<float> feature_values;
        feature_values.reserve(X.size());
        
        for (const auto& sample : X) {
            feature_values.push_back(sample[feature]);
        }
        
        std::sort(feature_values.begin(), feature_values.end());
        auto last = std::unique(feature_values.begin(), feature_values.end());
        feature_values.erase(last, feature_values.end());
        
        for (const auto& threshold : feature_values) {
            std::vector<float> left_y, right_y;
            
            for (size_t i = 0; i < X.size(); ++i) {
                if (X[i][feature] < threshold) {
                    left_y.push_back(y[i]);
                } else {
                    right_y.push_back(y[i]);
                }
            }
            
            if (left_y.empty() || right_y.empty()) {
                continue;
            }
            
            float mse = _mse(left_y, right_y);
            
            if (mse < best_mse) {
                best_mse = mse;
                best_feature = feature;
                best_threshold = threshold;
            }
        }
    }
    
    return {best_feature, best_threshold};
}

float RegTree::_mse(const std::vector<float>& left_y, const std::vector<float>& right_y){
    auto calculate_mse = [](const std::vector<float>& y) {
        float mean = 0.0f;
        for (const auto& val : y) {
            mean += val;
        }
        mean /= y.size();
        float sum = 0.0f;
        for (const auto& val : y) {
            sum += (val - mean) * (val - mean);
        }
        return sum / y.size();
    };
    
    int total_samples = left_y.size() + right_y.size();
    float left_mse = calculate_mse(left_y) * (static_cast<float>(left_y.size()) / total_samples);
    float right_mse = calculate_mse(right_y) * (static_cast<float>(right_y.size()) / total_samples);
    
    return (left_mse + right_mse);
}

float RegTree::_predict_one(const std::vector<float>& x, Node* node) const {
    if (node == nullptr) {
        std::cerr << "Warning: Null node" << std::endl;
        return 0.0f;
    }
    
    if (node->value != -1){
        return node->value;
    }
    
    if (x[node->feature] <= node->threshold){
        return _predict_one(x, node->left);
    } else {
        return _predict_one(x, node->right);
    }
}

std::vector<float> RegTree::predict(const std::vector<std::vector<float>>& X) const {
    std::vector<float> predictions;
    predictions.reserve(X.size());
    
    if (root == nullptr) {
        return std::vector<float>(X.size(), 0.0f);
    }
    
    for (const auto& x : X) {
        predictions.push_back(_predict_one(x, root));
    }
    
    return predictions;
}




