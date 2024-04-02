#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int maxRevenue(int n, vector<int>& prices, vector<int>& cuts) {
    vector<int> dp(n + 1, 0); // DP table to store maximum revenue

    // DP table update
    for (int i = 1; i <= n; ++i) {
        int max_val = INT_MIN;
        for (int j = 1; j <= i; ++j) {
            int revenue = prices[j - 1] + dp[i - j];
            if (revenue > max_val) {
                max_val = revenue;
                cuts[i] = j; // Track the cut that leads to maximum revenue
            }
        }
        dp[i] = max_val;
    }

    return dp[n];
}

void printCuts(int n, vector<int>& cuts) {
    while (n > 0) {
        cout << "Cut: " << cuts[n] << " pieces of length " << cuts[n] << endl;
        n -= cuts[n];
    }
}

int main() {
    int n = 5;
    vector<int> prices = {1, 2, 3, 4};

    vector<int> cuts(n + 1, 0); // Array to store the cuts
    int revenue = maxRevenue(n, prices, cuts);

    cout << "Rod length: " << n << " Prices: ";
    cout << "(";
    for (int i = 0; i < prices.size(); ++i) {
        cout << prices[i];
        if (i < prices.size() - 1) cout << ", ";
    }
    cout << ")" << endl;
    cout << "Maximum revenue: " << revenue << endl;

    // Print the cuts made
    printCuts(n, cuts);

    return 0;
}
