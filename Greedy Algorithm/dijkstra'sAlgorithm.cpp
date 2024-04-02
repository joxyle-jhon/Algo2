#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

// Structure to represent a weighted edge
struct Edge {
    char dest;
    int weight;
};

// Structure to represent a vertex and its distance from the source
struct Vertex {
    char id;
    int dist;
};

// Comparator function for priority queue
struct CompareDist {
    bool operator()(const Vertex& v1, const Vertex& v2) {
        return v1.dist > v2.dist;
    }
};

// Dijkstra's algorithm
void dijkstra(vector<vector<Edge>>& graph, char source) {
    // Initialize distances
    unordered_map<char, int> distances;
    for (const auto& edges : graph) {
        for (const auto& edge : edges) {
            distances[edge.dest] = INT_MAX;
        }
    }
    distances[source] = 0;

    // Initialize priority queue
    priority_queue<Vertex, vector<Vertex>, CompareDist> pq;
    pq.push({source, 0});

    // Main loop
    while (!pq.empty()) {
        Vertex u = pq.top();
        pq.pop();

        // Update distances for neighbors of u
        for (const auto& edge : graph[u.id]) {
            if (distances[u.id] + edge.weight < distances[edge.dest]) {
                distances[edge.dest] = distances[u.id] + edge.weight;
                pq.push({edge.dest, distances[edge.dest]});
            }
        }
    }

    // Output shortest paths
    cout << "Shortest paths: ";
    for (const auto& pair : distances) {
        if (pair.first != source) {
            cout << source << "-" << pair.first << ": " << pair.second << ", ";
        }
    }
    cout << endl;
}

int main() {
    // Weighted graph
    vector<vector<Edge>> graph = {
        {{'B', 2}, {'C', 4}},
        {{'D', 3}},
        {{'D', 1}, {'E', 7}},
        {},
        {}
    };

    // Source vertex
    char source = 'A';

    // Run Dijkstra's algorithm
    dijkstra(graph, source);

    return 0;
}
