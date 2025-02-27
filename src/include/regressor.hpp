#ifndef REGRESSOR_HPP
#define REGRESSOR_HPP

#include <vector>
#include <iostream>

class Regressor {
    private:
        int n_estimators;
        int max_depth;
        float learning_rate;
        int n_bins;
        std::string device;
    
    public:
        Regressor(int n_estimators = 100, 
                 int max_depth = 3, 
                 float learning_rate = 0.1f, 
                 int n_bins = 256, 
                 std::string device = "cpu");
        void fit(const std::vector<std::vector<float>>& X, const std::vector<float>& y);
        

};


#endif
