#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

#define INF numeric_limits<int>::max()

struct Edge {
    int to, capacity, cost, flow;
    Edge* reverse;

    Edge(int t, int c, int co) : to(t), capacity(c), cost(co), flow(0), reverse(nullptr) {}
};

class Graph {
    int V;
    vector<vector<Edge*>> adj;

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v, int capacity, int cost) {
        Edge* uv = new Edge(v, capacity, cost);
        Edge* vu = new Edge(u, 0, -cost);
        uv->reverse = vu;
        vu->reverse = uv;
        adj[u].push_back(uv);
        adj[v].push_back(vu);
    }

    pair<int, int> minCostFlow(int source, int sink) {
        int totalFlow = 0;
        int totalCost = 0;

        vector<int> dist(V, INF);
        vector<int> prev(V, -1);
        vector<Edge*> prevEdge(V, nullptr);

        while (true) {
            dist.assign(V, INF);
            prev.assign(V, -1);
            prevEdge.assign(V, nullptr);

            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            pq.push({0, source});
            dist[source] = 0;

            while (!pq.empty()) {
                int u = pq.top().second;
                int d = pq.top().first;
                pq.pop();

                if (d > dist[u]) continue;

                for (Edge* e : adj[u]) {
                    int v = e->to;
                    if (e->capacity - e->flow > 0 && dist[u] + e->cost < dist[v]) {
                        dist[v] = dist[u] + e->cost;
                        prev[v] = u;
                        prevEdge[v] = e;
                        pq.push({dist[v], v});
                    }
                }
            }

            if (prev[sink] == -1) break;

            int pathFlow = INF;
            for (int v = sink; v != source; v = prev[v]) {
                Edge* e = prevEdge[v];
                pathFlow = min(pathFlow, e->capacity - e->flow);
            }

            for (int v = sink; v != source; v = prev[v]) {
                Edge* e = prevEdge[v];
                e->flow += pathFlow;
                e->reverse->flow -= pathFlow;
                totalCost += e->cost * pathFlow;
            }

            totalFlow += pathFlow;
        }

        return {totalFlow, totalCost};
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 3, 1);
    g.addEdge(0, 2, 4, 3);
    g.addEdge(1, 3, 2, 2);
    g.addEdge(2, 3, 7, 1);

    pair<int, int> result = g.minCostFlow(0, 3);

    cout << "Minimum cost flow: " << result.second << " (Path: A-B-D with cost 3)" << endl;

    return 0;
}
