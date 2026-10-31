#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

// Structure to represent the state of the two jugs (jug1, jug2)
struct State {
    int x, y;
    vector<pair<int, int>> path;

    bool operator==(const State& other) const {
        return x == other.x && y == other.y;
    }
};

// Function to solve the Water Jug problem using Breadth-First Search (State Space Search)
void solveWaterJug(int cap1, int cap2, int target) {
    queue<State> q;
    set<pair<int, int>> visited;

    // Initial state: both jugs are empty
    State initial = {0, 0, {}};
    initial.path.push_back({0, 0});
    q.push(initial);
    visited.insert({0, 0});

    bool found = false;

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        // Check if target is reached in either jug
        if (curr.x == target || curr.y == target) {
            cout << "Target reached! Path of states (Jug1, Jug2):\n";
            for (auto p : curr.path) {
                cout << "(" << p.first << ", " << p.second << ")\n";
            }
            found = true;
            break;
        }

        // Possible rules / transitions
        vector<pair<int, int>> next_states = {
            {cap1, curr.y},                   // Fill Jug 1
            {curr.x, cap2},                   // Fill Jug 2
            {0, curr.y},                      // Empty Jug 1
            {curr.x, 0},                      // Empty Jug 2
            // Pour Jug 1 -> Jug 2
            {curr.x - min(curr.x, cap2 - curr.y), curr.y + min(curr.x, cap2 - curr.y)},
            // Pour Jug 2 -> Jug 1
            {curr.x + min(curr.y, cap1 - curr.x), curr.y - min(curr.y, cap1 - curr.x)}
        };

        for (auto ns : next_states) {
            if (visited.find({ns.first, ns.second}) == visited.end()) {
                visited.insert({ns.first, ns.second});
                State next_state = {ns.first, ns.second, curr.path};
                next_state.path.push_back({ns.first, ns.second});
                q.push(next_state);
            }
        }
    }

    if (!found) {
        cout << "Solution not possible.\n";
    }
}

int main() {
    int cap1 = 4, cap2 = 3, target = 2;
    cout << "--- Water Jug Problem (AI State Space Search) ---\n";
    solveWaterJug(cap1, cap2, target);
    return 0;
}