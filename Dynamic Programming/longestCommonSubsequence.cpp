#include <iostream>
#include <vector>
#include <string>

using namespace std;

string longestCommonSubsequence(string X, string Y) {
    int m = X.length();
    int n = Y.length();

    // Create and initialize DP table
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // DP table update
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Finding the LCS
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs = X[i - 1] + lcs;
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return lcs;
}

int main() {
    string X = "AGTGAT";
    string Y = "TGATCA";

    string lcs = longestCommonSubsequence(X, Y);
    int length = lcs.length();

    cout << "Sequences: X = \"" << X << "\" Y = \"" << Y << "\"" << endl;
    cout << "Length of LCS: " << length << " (LCS: \"" << lcs << "\")" << endl;

    return 0;
}
