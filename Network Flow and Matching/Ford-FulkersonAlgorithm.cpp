#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 1e9;

// Structure to represent an edge in the flow network
struct Edge {
    int v, u, capacity, flow;
};

// Ford-Fulkerson algorithm
int fordFulkerson(vector<vector<Edge>>& graph, int source, int sink) {
    int maxFlow = 0;

    // Initialize residual capacities of edges
    vector<vector<int>> residual(graph.size(), vector<int>(graph.size(), 0));
    for (const auto& edges : graph) {
        for (const auto& edge : edges) {
            residual[edge.v][edge.u] += edge.capacity;
        }
    }

    // Repeat until no augmenting path can be found
    while (true) {
        // Use BFS to find an augmenting path
        vector<int> parent(graph.size(), -1);
        queue<int> q;
        q.push(source);
        while (!q.empty() && parent[sink] == -1) {
            int u = q.front();
            q.pop();
            for (const auto& edge : graph[u]) {
                if (parent[edge.u] == -1 && residual[u][edge.u] > 0) {
                    parent[edge.u] = u;
                    q.push(edge.u);
                }
            }
        }

        // If no augmenting path is found, break
        if (parent[sink] == -1) break;

        // Find bottleneck capacity along the augmenting path
        int bottleneck = INF;
        for (int u = sink; u != source; u = parent[u]) {
            int v = parent[u];
            bottleneck = min(bottleneck, residual[v][u]);
        }

        // Update flow and residual capacities along the augmenting path
        for (int u = sink; u != source; u = parent[u]) {
            int v = parent[u];
            residual[v][u] -= bottleneck;
            residual[u][v] += bottleneck;
        }

        // Add bottleneck flow to maximum flow
        maxFlow += bottleneck;
    }

    return maxFlow;
}

int main() {
    // Sample input
    vector<vector<Edge>> graph = {
        {{0, 1, 3, 0}, {1, 3, 2, 0}}, // A -> B (capacity: 3), B -> D (capacity: 2)
        {{0, 2, 4, 0}, {2, 3, 7, 0}}  // A -> C (capacity: 4), C -> D (capacity: 7)
    };

    // Source and sink vertices
    int source = 0, sink = 3;

    // Run Ford-Fulkerson algorithm
    int maxFlow = fordFulkerson(graph, source, sink);

    // Output
    cout << "Network: (source: " << (char)('A' + source) << ", sink: " << (char)('A' + sink) << ")" << endl;
    cout << "Maximum flow: " << maxFlow << " (Augmenting paths: ";
    // Iterate over edges to find augmenting paths
    for (const auto& edges : graph) {
        for (const auto& edge : edges) {
            if (edge.flow > 0) {
                cout << (char)('A' + edge.v) << "-";
                cout << (char)('A' + edge.u) << ", ";
            }
        }
    }
    cout << ")" << endl;

    return 0;
}
