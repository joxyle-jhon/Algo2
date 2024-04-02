#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Helper function to print the optimal BST structure
void printOptimalBST(vector<vector<int>>& root, int i, int j, int parent, const vector<string>& keys) {
    if (i <= j) {
        int currentRoot = root[i][j];
        if (parent == -1) {
            cout << "root: " << keys[currentRoot];
        } else if (i == parent) {
            cout << "left: " << keys[currentRoot];
        } else {
            cout << "right: " << keys[currentRoot];
        }
        if (i != j) {
            cout << ", ";
        }
        printOptimalBST(root, i, currentRoot - 1, currentRoot, keys); // Left subtree
        printOptimalBST(root, currentRoot + 1, j, currentRoot, keys); // Right subtree
    }
}

void optimalBST(vector<string>& keys, vector<int>& frequencies) {
    int n = keys.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> root(n + 1, vector<int>(n + 1, 0));

    // Initialize diagonal elements with frequencies
    for (int i = 0; i < n; ++i) {
        dp[i][i] = frequencies[i];
        root[i][i] = i;
    }

    // DP table update
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            dp[i][j] = numeric_limits<int>::max();
            for (int k = i; k <= j; ++k) {
                int cost = ((k > i) ? dp[i][k - 1] : 0) + ((k < j) ? dp[k + 1][j] : 0);
                cost += frequencies[k];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    root[i][j] = k;
                }
            }
        }
    }

    // Reconstruct the optimal BST structure
    cout << "Optimal BST: (";
    printOptimalBST(root, 0, n - 1, -1, keys);
    cout << ")" << endl;
}

int main() {
    vector<string> keys = {"A", "B", "C", "D"};
    vector<int> frequencies = {2, 3, 1, 4};

    optimalBST(keys, frequencies);

    return 0;
}
