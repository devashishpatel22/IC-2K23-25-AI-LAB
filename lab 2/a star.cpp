#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <unordered_map>

// --- Coordinate Struct ---
struct Point {
    int x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

// Custom hash function so Point can be used in unordered maps/sets
struct PointHash {
    size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

// --- Node Structure for Priority Queue ---
struct Node {
    Point pos;
    double g_cost; // Exact cost from start to current node
    double h_cost; // Heuristic estimated cost from current node to goal
    double f_cost() const { return g_cost + h_cost; }

    // Min-heap comparator: we want the node with the LOWEST f_cost at the top
    bool operator>(const Node& other) const {
        return f_cost() > other.f_cost();
    }
};

class AStarPathfinder {
private:
    int m_width;
    int m_height;
    std::vector<std::vector<int>> m_grid; // 0 = walkable, 1 = obstacle

    // Heuristic function: Manhattan Distance (ideal for grid movement)
    double heuristic(Point a, Point b) const {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }

    bool is_valid(Point p) const {
        return p.x >= 0 && p.x < m_width && p.y >= 0 && p.y < m_height && m_grid[p.y][p.x] == 0;
    }

public:
    AStarPathfinder(int width, int height, const std::vector<std::vector<int>>& grid)
        : m_width(width), m_height(height), m_grid(grid) {}

    // Find the shortest path from start to goal
    std::vector<Point> find_path(Point start, Point goal) {
        if (!is_valid(start) || !is_valid(goal)) {
            std::cerr << "[Error] Start or Goal is out of bounds or blocked!\n";
            return {};
        }

        // Priority queue for open set (min-heap)
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open_set;

        // Track costs and path reconstruction
        std::unordered_map<Point, double, PointHash> g_costs;
        std::unordered_map<Point, Point, PointHash> came_from;
        std::unordered_map<Point, bool, PointHash> closed_set;

        // Initialize start node
        open_set.push({start, 0.0, heuristic(start, goal)});
        g_costs[start] = 0.0;

        // 4-directional movement (Up, Down, Left, Right)
        const std::vector<Point> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        while (!open_set.empty()) {
            Node current = open_set.top();
            open_set.pop();

            // If we reached the goal, reconstruct and return the path
            if (current.pos == goal) {
                std::vector<Point> path;
                Point curr = goal;
                while (curr != start) {
                    path.push_back(curr);
                    curr = came_from[curr];
                }
                path.push_back(start);
                std::reverse(path.begin(), path.end());
                return path;
            }

            // Skip if already evaluated
            if (closed_set[current.pos]) continue;
            closed_set[current.pos] = true;

            // Explore neighbors
            for (const auto& dir : directions) {
                Point neighbor{current.pos.x + dir.x, current.pos.y + dir.y};

                if (!is_valid(neighbor) || closed_set[neighbor]) {
                    continue;
                }

                double tentative_g = g_costs[current.pos] + 1.0; // Cost between adjacent cells is 1

                if (g_costs.find(neighbor) == g_costs.end() || tentative_g < g_costs[neighbor]) {
                    g_costs[neighbor] = tentative_g;
                    double h = heuristic(neighbor, goal);
                    open_set.push({neighbor, tentative_g, h});
                    came_from[neighbor] = current.pos;
                }
            }
        }

        std::cout << "[Info] No path found to target!\n";
        return {}; // No path exists
    }
};

// ==========================================
// Example Usage: Grid Pathfinding
// ==========================================
int main() {
    // Define a 5x5 grid (0 = Open Path, 1 = Obstacle)
    int width = 5;
    int height = 5;
    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };

    Point start = {0, 0};
    Point goal = {4, 4};

    AStarPathfinder pathfinder(width, height, grid);
    std::vector<Point> path = pathfinder.find_path(start, goal);

    if (!path.empty()) {
        std::cout << "Optimal Path Found (" << path.size() - 1 << " steps):\n";
        for (const auto& p : path) {
            std::cout << "(" << p.x << ", " << p.y << ") ";
        }
        std::cout << "\n";
    }

    return 0;
}