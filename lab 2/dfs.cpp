#include <iostream>
#include <vector>
#include <algorithm>

class Graph {
private:
    int m_vertices;
    std::vector<std::vector<int>> m_adj_list;

    // Helper recursive function for DFS
    void dfs_helper(int current, std::vector<bool>& visited) const {
        // Mark the current node as visited and process it
        visited[current] = true;
        std::cout << current << " ";

        // Recur for all adjacent neighbors
        for (int neighbor : m_adj_list[current]) {
            if (!visited[neighbor]) {
                dfs_helper(neighbor, visited);
            }
        }
    }

public:
    explicit Graph(int vertices) : m_vertices(vertices), m_adj_list(vertices) {}

    // Add an undirected edge between u and v
    void add_edge(int u, int v) {
        if (u >= 0 && u < m_vertices && v >= 0 && v < m_vertices) {
            m_adj_list[u].push_back(v);
            m_adj_list[v].push_back(u); // Remove this line if the graph is directed
        }
    }

    // Depth-First Search traversal starting from 'start_node'
    void dfs(int start_node) const {
        if (start_node < 0 || start_node >= m_vertices) {
            std::cerr << "[Error] Start node out of bounds!\n";
            return;
        }

        // Track visited nodes to prevent infinite loops in cycles
        std::vector<bool> visited(m_vertices, false);

        std::cout << "DFS Traversal starting from node " << start_node << ": ";
        dfs_helper(start_node, visited);
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

    // Run DFS starting from node 0
    g.dfs(0);

    return 0;
}