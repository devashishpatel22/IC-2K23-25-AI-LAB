#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <functional>
#include <algorithm>

// --- Rule Class ---
class Rule {
public:
    std::string name;
    std::function<bool(const std::unordered_set<std::string>&)> condition;
    std::function<void(std::unordered_set<std::string>&)> action;

    Rule(std::string n, 
         std::function<bool(const std::unordered_set<std::string>&)> cond,
         std::function<void(std::unordered_set<std::string>&)> act)
        : name(std::move(n)), condition(std::move(cond)), action(std::move(act)) {}
};

// --- Production System / Inference Engine ---
class ProductionSystem {
private:
    std::vector<Rule> rules;
    std::unordered_set<std::string> facts;

public:
    void add_rule(Rule rule) {
        rules.push_back(std::move(rule));
    }

    void add_fact(const std::string& fact) {
        // insert returns a pair; second is true if the element was added
        if (facts.insert(fact).second) {
            std::cout << "[Fact Added]   : " << fact << "\n";
        }
    }

    void run() {
        std::cout << "\n--- Starting Inference Engine (Recognize-Act Cycle) ---\n";
        bool fired = true;
        int iteration = 0;

        // Forward chaining loop: keeps running until no new rules fire
        while (fired) {
            fired = false;
            iteration++;
            std::cout << "\n--- Iteration " << iteration << " ---\n";

            for (auto& rule : rules) {
                // Check if condition is met
                if (rule.condition(facts)) {
                    std::cout << " -> Rule Fired: " << rule.name << "\n";
                    rule.action(facts);
                    fired = true;
                    break; // Restart cycle to re-evaluate rules with updated facts
                }
            }
        }
        std::cout << "\n--- Inference Complete ---\n";
    }

    void print_facts() const {
        std::cout << "\nFinal Working Memory Facts:\n";
        std::vector<std::string> sorted_facts(facts.begin(), facts.end());
        std::sort(sorted_facts.begin(), sorted_facts.end());
        for (const auto& fact : sorted_facts) {
            std::cout << " - " << fact << "\n";
        }
    }
};

// ==========================================
// Example Usage: Animal Classification Expert System
// ==========================================
int main() {
    ProductionSystem engine;

    // 1. Set Initial Facts in Working Memory
    std::cout << "Initializing Working Memory...\n";
    engine.add_fact("has_hair");
    engine.add_fact("gives_milk");

    // 2. Define Production Rules using C++ Lambdas

    // Rule 1: If it has hair, it's a mammal
    engine.add_rule(Rule(
        "Rule_Mammal_Hair",
        [](const std::unordered_set<std::string>& f) { 
            return f.count("has_hair") && !f.count("is_mammal"); 
        },
        [](std::unordered_set<std::string>& f) { 
            f.insert("is_mammal"); 
        }
    ));

    // Rule 2: If it gives milk, it's a mammal
    engine.add_rule(Rule(
        "Rule_Mammal_Milk",
        [](const std::unordered_set<std::string>& f) { 
            return f.count("gives_milk") && !f.count("is_mammal"); 
        },
        [](std::unordered_set<std::string>& f) { 
            f.insert("is_mammal"); 
        }
    ));

    // Rule 3: If it's a mammal and has sharp teeth, it's a carnivore
    engine.add_rule(Rule(
        "Rule_Carnivore",
        [](const std::unordered_set<std::string>& f) { 
            return f.count("is_mammal") && f.count("has_sharp_teeth") && !f.count("is_carnivore"); 
        },
        [](std::unordered_set<std::string>& f) { 
            f.insert("is_carnivore"); 
        }
    ));

    // Rule 4: If it's a mammal, give it sharp teeth (simulated trait acquisition)
    engine.add_rule(Rule(
        "Rule_Acquire_Teeth",
        [](const std::unordered_set<std::string>& f) { 
            return f.count("is_mammal") && !f.count("has_sharp_teeth") && !f.count("is_carnivore"); 
        },
        [](std::unordered_set<std::string>& f) { 
            f.insert("has_sharp_teeth"); 
        }
    ));

    // Rule 5: If it's a carnivore with tawny color and dark spots, it's a cheetah
    engine.add_rule(Rule(
        "Rule_Identify_Cheetah",
        [](const std::unordered_set<std::string>& f) { 
            return f.count("is_carnivore") && f.count("has_tawny_color") && f.count("has_dark_spots") && !f.count("is_cheetah"); 
        },
        [](std::unordered_set<std::string>& f) { 
            f.insert("is_cheetah"); 
        }
    ));

    // Add extra physical traits midway to trigger final identification
    engine.add_fact("has_tawny_color");
    engine.add_fact("has_dark_spots");

    // 3. Run the Inference Engine
    engine.run();

    // 4. View Final State
    engine.print_facts();

    return 0;
}