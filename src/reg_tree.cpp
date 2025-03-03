#include "reg_tree.hpp"
#include <algorithm>

Tree::Tree(int max_depth) : max_depth(max_depth) {
    root = nullptr;
}

void Tree::fit(const std::vector<std::vector<float>>& X, const std::vector<float>& y){
    root = _build_tree(X, y, 0);
}

Node* Tree::_build_tree(const std::vector<std::vector<float>>& X, const std::vector<float>& y, int depth){
    int sample_count = X.size();
    int feature_count = X[0].size();

}


std::pair<int, float> Tree::_best_split(const std::vector<std::vector<float>>& X, const std::vector<float>& y, int feature_count){
    float best_mse = std::numeric_limits<float>::max();
    int best_feature = 0;
    float best_threshold = 0;

}

float Tree::_mse(const std::vector<float>& left_y, const std::vector<float>& right_y){
}


float Tree::_predict_one(const std::vector<float>& x, Node* node){

}

std::vector<float> Tree::predict(const std::vector<std::vector<float>>& X){
    
}




