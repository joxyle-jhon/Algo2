#include <iostream>
#include <vector>

using namespace std;

// Structure to represent an edge in the circulation network
struct Edge {
    int from, to; // Nodes
    int capacity, flow;
};

// Structure to represent a circulation network
struct CirculationNetwork {
    int nodes;
    vector<Edge> edges;
};

// Function to check if the circulation network is feasible
bool isFeasible(CirculationNetwork& circulation) {
    vector<int> netFlow(circulation.nodes, 0);

    // Calculate net flow at each node
    for (const auto& edge : circulation.edges) {
        netFlow[edge.to] += edge.flow;
        netFlow[edge.from] -= edge.flow;
    }

    // Check if net flow at each node is zero (except source and sink)
    for (int i = 1; i < circulation.nodes - 1; ++i) {
        if (netFlow[i] != 0) {
            return false; // Not feasible
        }
    }

    return true; // Feasible
}

// Function to find a feasible flow in the circulation network
void findFeasibleFlow(CirculationNetwork& circulation) {
    if (!isFeasible(circulation)) {
        cout << "Circulation network is not feasible!" << endl;
        return;
    }

    // Find a feasible flow algorithm (e.g., Cycle-Canceling algorithm or Capacity-Scaling algorithm)
    // Implement the algorithm here

    // Output the flow along each edge
    cout << "Feasible Flow:" << endl;
    for (const auto& edge : circulation.edges) {
        cout << edge.from << " -> " << edge.to << " (" << edge.flow << ")" << endl;
    }
}

int main() {
    // Sample input
    CirculationNetwork circulation = {
        4, // Number of nodes
        {{0, 1, 3, 0}, {1, 2, 2, 0}, {2, 0, 4, 0}} // Edges: {from, to, capacity, flow}
    };

    // Find a feasible flow in the circulation network
    findFeasibleFlow(circulation);

    return 0;
}
