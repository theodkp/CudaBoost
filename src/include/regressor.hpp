#ifndef REGRESSOR_HPP
#define REGRESSOR_HPP

#include <vector>
#include <iostream>
#include "reg_tree.hpp"

class Regressor {
    private:
        int n_estimators;
        int max_depth;
        float learning_rate;
        std::string device;
        float initial_prediction;
        std::vector<RegTree> trees;


    public:
        Regressor(int n_estimators = 100, 
                 int max_depth = 3, 
                 float learning_rate = 0.1f, 
                 std::string device = "cpu",
                 float initial_prediction = 0.0f);
                 
        void fit(const std::vector<std::vector<float>>& X, const std::vector<float>& y);
        std::vector<float> predict(const std::vector<std::vector<float>>& X) const;
};

#endif
