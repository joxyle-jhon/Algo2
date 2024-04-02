#include <iostream>
#include <vector>

using namespace std;

bool subsetSum(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // Base cases
    dp[0][0] = true;

    // Initialize first row (excluding any element)
    for (int j = 1; j <= target; ++j) {
        dp[0][j] = false;
    }

    // DP table update
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= target; ++j) {
            dp[i][j] = dp[i - 1][j]; // Exclude current element
            if (j >= nums[i - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]]; // Include current element
            }
        }
    }

    return dp[n][target];
}

int main() {
    vector<int> nums = {3, 2, 7};
    int target = 5;

    if (subsetSum(nums, target)) {
        cout << "Result: True (Subset: ";
        // Reconstruct the subset
        bool first = true;
        for (int i = 0; i < nums.size(); ++i) {
            if (subsetSum(nums, target - nums[i])) {
                if (!first) cout << ", ";
                cout << nums[i];
                first = false;
                target -= nums[i];
            }
        }
        cout << ")" << endl;
    } else {
        cout << "Result: False" << endl;
    }

    return 0;
}
