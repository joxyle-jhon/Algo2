#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

bool wordBreak(string s, unordered_set<string>& wordDict) {
    int n = s.length();
    vector<bool> dp(n + 1, false);
    dp[0] = true; // Base case: empty string is always present in dictionary

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end()) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}

int main() {
    unordered_set<string> wordDict = {"apple", "pear", "pie"};
    string s = "applepie";

    if (wordBreak(s, wordDict)) {
        cout << "Result: True (\"" << s << "\")" << endl;
    } else {
        cout << "Result: False" << endl;
    }

    return 0;
}
