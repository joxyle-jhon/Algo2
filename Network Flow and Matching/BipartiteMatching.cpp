#include <iostream>
#include <vector>

using namespace std;

const int UNMATCHED = -1;

// Function to perform DFS and find an augmenting path
bool dfs(int u, vector<vector<int>>& graph, vector<int>& match, vector<bool>& visited) {
    for (int v : graph[u]) {
        if (!visited[v]) {
            visited[v] = true;
            if (match[v] == UNMATCHED || dfs(match[v], graph, match, visited)) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

// Function to find maximum matching in a bipartite graph
int bipartiteMatching(vector<vector<int>>& graph, int n, int m) {
    vector<int> match(m, UNMATCHED);
    int matching = 0;
    for (int i = 0; i < n; ++i) {
        vector<bool> visited(m, false);
        if (dfs(i, graph, match, visited)) {
            ++matching;
        }
    }
    return matching;
}

int main() {
    // Sample input
    vector<vector<int>> graph = {
        {0, 1}, // P1 (Web Dev) - E1 (Web, Data)
        {0, 2}, // P1 (Web Dev) - E2 (Data, Mobile)
        {1, 2}, // P2 (Data Science) - E2 (Data, Mobile)
    };

    int n = 3; // Number of projects
    int m = 3; // Number of employees

    // Find maximum matching
    int maxMatching = bipartiteMatching(graph, n, m);

    // Output maximum matching
    cout << "Maximum Matching: " << maxMatching << " (Total edges: " << maxMatching << ")" << endl;

    return 0;
}
