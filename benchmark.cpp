#include "RBTree.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace std::chrono;

// bst
class SimpleBSTNode {
public:
    int data;
    SimpleBSTNode *left, *right;
    SimpleBSTNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

class SimpleBST {
public:
    SimpleBSTNode* root = nullptr;
    
    void insert(int data) { root = insertRecursive(root, data); }
    SimpleBSTNode* insertRecursive(SimpleBSTNode* node, int data) {
        if (!node) return new SimpleBSTNode(data);
        if (data < node->data) node->left = insertRecursive(node->left, data);
        else node->right = insertRecursive(node->right, data);
        return node;
    }

    int getHeight(SimpleBSTNode* node) {
        if (!node) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }
};

//The Benchmark Execution
int main() {
    const int N = 10000; // Dataset size
    RBTree rbt;
    SimpleBST bst;

    cout << "--- RED-BLACK TREE VS BST BENCHMARK ---" << endl;
    cout << "Testing with " << N << " sorted elements..." << endl;

    // 1. Measure RBT Insertion (Sorted)
    auto start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) rbt.insert(i);
    auto stop = high_resolution_clock::now();
    auto rbtTime = duration_cast<microseconds>(stop - start);

    // 2. Measure BST Insertion (Sorted)
    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) bst.insert(i);
    stop = high_resolution_clock::now();
    auto bstTime = duration_cast<microseconds>(stop - start);

    // 3. Results Comparison
    cout << "\n[RESULT: HEIGHT]" << endl;
    cout << "Normal BST Height: " << bst.getHeight(bst.root) << " (O(N) - Linear)" << endl;
    cout << "Red-Black Tree Height: " << rbt.getHeight(rbt.getRoot()) << " (O(log N) - Balanced)" << endl;

    cout << "\n[RESULT: INSERTION TIME]" << endl;
    cout << "Normal BST Time: " << bstTime.count() << " us" << endl;
    cout << "Red-Black Tree Time: " << rbtTime.count() << " us" << endl;

    // Save to CSV for your Project Report
    ofstream results("results.csv");
    results << "TreeType,Height,Time(us)\n";
    results << "BST," << bst.getHeight(bst.root) << "," << bstTime.count() << "\n";
    results << "RBT," << rbt.getHeight(rbt.getRoot()) << "," << rbtTime.count() << "\n";
    results.close();

    cout << "\nResults saved to results.csv" << endl;
    return 0;
}