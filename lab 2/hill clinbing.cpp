#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <iomanip>
#include <random>

// Define a state/point as a vector of doubles
using State = std::vector<double>;

// Define the objective function type: takes a State and returns a double (score to maximize)
using ObjectiveFunction = std::function<double(const State&)>;

class HillClimbing {
private:
    ObjectiveFunction m_objective;
    double m_step_size;
    double m_epsilon; // Convergence tolerance
    int m_max_iterations;

public:
    HillClimbing(ObjectiveFunction obj, double step_size = 0.05, double epsilon = 1e-6, int max_iterations = 1000)
        : m_objective(std::move(obj)), m_step_size(step_size), m_epsilon(epsilon), m_max_iterations(max_iterations) {}

    struct Result {
        State best_state;
        double best_score;
        int iterations;
        bool converged;
    };

    // Generates neighbors by taking a small step (+/- step_size) along each dimension
    std::vector<State> get_neighbors(const State& current) const {
        std::vector<State> neighbors;
        size_t dim = current.size();

        // For each dimension, generate two neighbors (forward and backward step)
        for (size_t i = 0; i < dim; ++i) {
            // Positive step
            State neighbor_pos = current;
            neighbor_pos[i] += m_step_size;
            neighbors.push_back(neighbor_pos);

            // Negative step
            State neighbor_neg = current;
            neighbor_neg[i] -= m_step_size;
            neighbors.push_back(neighbor_neg);
        }

        return neighbors;
    }

    Result optimize(const State& initial_state) {
        State current = initial_state;
        double current_score = m_objective(current);
        int iter = 0;

        std::cout << "[Hill Climbing] Starting optimization...\n";

        while (iter < m_max_iterations) {
            iter++;
            std::vector<State> neighbors = get_neighbors(current);
            
            State best_neighbor = current;
            double best_neighbor_score = current_score;

            // Evaluate all neighbors to find the steepest ascent
            for (const auto& neighbor : neighbors) {
                double score = m_objective(neighbor);
                if (score > best_neighbor_score) {
                    best_neighbor_score = score;
                    best_neighbor = neighbor;
                }
            }

            // If no neighbor improved the score, we have reached a local peak
            if (best_neighbor_score <= current_score + m_epsilon) {
                return {current, current_score, iter, true};
            }

            // Move to the best neighbor
            current = best_neighbor;
            current_score = best_neighbor_score;
        }

        return {current, current_score, iter, false}; // Reached max iterations
    }
};

// ==========================================
// Example Usage: Maximizing a 2D Function
// ==========================================
int main() {
    // Define a sample 2D objective function to maximize:
    // f(x, y) = 20 - (x - 3.5)^2 - (y - 5.0)^2
    // This has a clear global maximum peak at (x=3.5, y=5.0) with a score of 20.
    ObjectiveFunction objective = [](const State& s) {
        double x = s[0];
        double y = s[1];
        return 20.0 - std::pow(x - 3.5, 2) - std::pow(y - 5.0, 2);
    };

    // Starting point (poor initial guess)
    State initial_guess = {0.0, 0.0};

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Initial Guess: x = " << initial_guess[0] 
              << ", y = " << initial_guess[1] 
              << " | Score = " << objective(initial_guess) << "\n\n";

    // Initialize optimizer with a step size of 0.1
    HillClimbing climber(objective, 0.1, 1e-6, 500);
    auto result = climber.optimize(initial_guess);

    // Print Results
    std::cout << "\n--- Optimization Complete ---\n";
    std::cout << "Converged     : " << (result.converged ? "Yes (Local/Global Peak Reached)" : "No (Max Iterations)") << "\n";
    std::cout << "Iterations    : " << result.iterations << "\n";
    std::cout << "Optimal X     : " << result.best_state[0] << "\n";
    std::cout << "Optimal Y     : " << result.best_state[1] << "\n";
    std::cout << "Max Score     : " << result.best_score << "\n";

    return 0;
}