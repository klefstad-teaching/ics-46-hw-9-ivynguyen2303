#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    distance[source] = 0;
    pq.emplace(0, source);

    while (!pq.empty()) {
        int dist_u = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.emplace(distance[v], v);
            }
        }
    }

    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int totalCost) {
    for (size_t i = 0; i < path.size(); ++i)
        cout << path[i] << " ";
    cout << endl << "Total cost is " << totalCost << endl;
}
