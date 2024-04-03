#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Function to perform topological sorting using Kahn's Algorithm
vector<int> topologicalSort(vector<vector<int>>& graph, vector<int>& inDegree) {
    int vertices = graph.size();
    vector<int> topoOrder;

    // Queue to store vertices with in-degree 0
    queue<int> q;
    for (int i = 0; i < vertices; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    // Perform topological sorting
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        // Remove edges from u and update in-degree of adjacent vertices
        for (int v : graph[u]) {
            if (--inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // If the size of topoOrder is not equal to the number of vertices, the graph contains a cycle
    if (topoOrder.size() != vertices) {
        topoOrder.clear(); // Clear the list to indicate failure
    }

    return topoOrder;
}

int main() {
    // Sample input
    vector<vector<int>> graph = {
        {},        // A has no incoming edges
        {0},       // B has 1 incoming edge from A
        {0},       // C has 1 incoming edge from A
        {1, 2},    // D has 2 incoming edges from B and C
        {3},       // E has 1 incoming edge from D
        {3},       // F has 1 incoming edge from D
        {3}        // G has 1 incoming edge from D
    };

    int vertices = graph.size();

    // Calculate in-degree of each vertex
    vector<int> inDegree(vertices, 0);
    for (int u = 0; u < vertices; ++u) {
        for (int v : graph[u]) {
            inDegree[v]++;
        }
    }

    // Perform topological sorting
    vector<int> topoOrder = topologicalSort(graph, inDegree);

    // Output the topological ordering
    if (topoOrder.empty()) {
        cout << "Graph contains a cycle. Topological sorting not possible." << endl;
    } else {
        cout << "Topological Ordering: ";
        for (int vertex : topoOrder) {
            cout << (char)('A' + vertex) << ", ";
        }
        cout << endl;
    }

    return 0;
}
