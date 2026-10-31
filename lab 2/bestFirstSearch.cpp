#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

// Comparator for priority queue to get the node with the lowest heuristic value
struct Compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // Min-heap based on heuristic value
    }
};

// Function to perform Best-First Search
void bestFirstSearch(int source, int goal, map<int, vector<pair<int, int>>>& graph, map<int, int>& heuristic) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    map<int, bool> visited;
    map<int, int> parent;

    pq.push({source, heuristic[source]});
    visited[source] = true;
    parent[source] = -1;

    bool reached = false;

    while (!pq.empty()) {
        int curr = pq.top().first;
        pq.pop();

        if (curr == goal) {
            reached = true;
            break;
        }

        for (auto neighbor : graph[curr]) {
            int next_node = neighbor.first;
            if (!visited[next_node]) {
                visited[next_node] = true;
                parent[next_node] = curr;
                pq.push({next_node, heuristic[next_node]});
            }
        }
    }

    if (reached) {
        cout << "Goal " << goal << " found using Best-First Search!\nPath: ";
        vector<int> path;
        int curr = goal;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        cout << "\n";
    } else {
        cout << "Goal could not be reached.\n";
    }
}

int main() {
    // Graph representation: adjacency list {node -> {neighbor, cost}}
    map<int, vector<pair<int, int>>> graph;
    graph[1] = {{2, 1}, {3, 3}};
    graph[2] = {{4, 1}, {5, 5}};
    graph[3] = {{6, 2}};
    graph[4] = {{7, 2}};
    graph[5] = {{7, 4}};
    graph[6] = {{7, 1}};

    // Heuristic values (straight-line distance or estimation to goal node 7)
    map<int, int> heuristic;
    heuristic[1] = 7;
    heuristic[2] = 6;
    heuristic[3] = 4;
    heuristic[4] = 2;
    heuristic[5] = 3;
    heuristic[6] = 1;
    heuristic[7] = 0;

    cout << "--- Best-First Search (Heuristic Technique) ---\n";
    bestFirstSearch(1, 7, graph, heuristic);

    return 0;
}