#ifndef REG_TREE_HPP
#define REG_TREE_HPP

#include <vector>
#include <iostream>

struct Node {
    int feature;
    float threshold;
    float value;
    Node* left;
    Node* right;

    Node(int f, float t, float v, Node* l = nullptr, Node* r = nullptr)
    : feature(f), threshold(t), value(v), left(l), right(r) {}

    Node(float val) : feature(-1), threshold(0.0f), value(val), left(nullptr), right(nullptr) {}

    ~Node() {
        delete left;
        delete right;
    }
};

// smart pointer?
inline Node* copyNode(const Node* src) {
    if (src == nullptr) return nullptr;
    
    Node* newNode = new Node(src->feature, src->threshold, src->value, 
                            copyNode(src->left), copyNode(src->right));
    return newNode;
}

class RegTree{
    private:
        Node* root;
        int max_depth;

        Node* _build_tree(const std::vector<std::vector<float>>& X, const std::vector<float>& y, int depth);
        float _mse(const std::vector<float>& left_y, const std::vector<float>& right_y);
        std::pair<int, float> _best_split(const std::vector<std::vector<float>>& X, const std::vector<float>& y, int feature_count);
        float _predict_one(const std::vector<float>& x, Node* node) const;

    public:
        RegTree(int max_depth = 3);
        
        RegTree(const RegTree& other) : max_depth(other.max_depth) {
            root = copyNode(other.root);
        }
        
        RegTree& operator=(const RegTree& other) {
            if (this != &other) {
                delete root;
                max_depth = other.max_depth;
                root = copyNode(other.root);
            }
            return *this;
        }
        
        void fit(const std::vector<std::vector<float>>& X, const std::vector<float>& y);
        std::vector<float> predict(const std::vector<std::vector<float>>& X) const;

        ~RegTree(){
            delete root;
        }
};

#endif
