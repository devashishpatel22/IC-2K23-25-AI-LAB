#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class Graph {
private:
    int m_vertices;
    std::vector<std::vector<int>> m_adj_list;

public:
    explicit Graph(int vertices) : m_vertices(vertices), m_adj_list(vertices) {}

    // Add an undirected edge between u and v
    void add_edge(int u, int v) {
        if (u >= 0 && u < m_vertices && v >= 0 && v < m_vertices) {
            m_adj_list[u].push_back(v);
            m_adj_list[v].push_back(u); // Remove this line if the graph is directed
        }
    }

    // Breadth-First Search traversal starting from 'start_node'
    void bfs(int start_node) const {
        if (start_node < 0 || start_node >= m_vertices) {
            std::cerr << "[Error] Start node out of bounds!\n";
            return;
        }

        // Track visited nodes to prevent cycles and redundant processing
        std::vector<bool> visited(m_vertices, false);
        std::queue<int> q;

        // Initialize BFS with the start node
        visited[start_node] = true;
        q.push(start_node);

        std::cout << "BFS Traversal starting from node " << start_node << ": ";

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            std::cout << current << " ";

            // Traverse all adjacent neighbors of the current node
            for (int neighbor : m_adj_list[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        std::cout << "\n";
    }
};

// ==========================================
// Example Usage
// ==========================================
int main() {
    // Create a graph with 6 vertices (0 through 5)
    Graph g(6);

    // Build the graph edges
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 4);
    g.add_edge(2, 5);

    // Run BFS starting from node 0
    g.bfs(0);

    return 0;
}