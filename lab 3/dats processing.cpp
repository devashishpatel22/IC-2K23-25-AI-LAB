#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <iomanip>

// --- 1. Data Model Structure ---
struct SalesRecord {
    int id;
    std::string category;
    double amount;
    bool is_valid;
};

// --- 2. Data Processing Engine ---
class DataProcessor {
public:
    // Parse a raw CSV string line into a SalesRecord safely
    static SalesRecord parse_csv_line(const std::string& line) {
        std::stringstream ss(line);
        std::string segment;
        SalesRecord record{0, "", 0.0, true};

        try {
            // Read ID
            if (std::getline(ss, segment, ',')) {
                record.id = std::stoi(segment);
            }
            // Read Category
            if (std::getline(ss, record.category, ',')) {
                // Trim spaces if necessary
                record.category.erase(0, record.category.find_first_not_of(" \t"));
                record.category.erase(record.category.find_last_not_of(" \t") + 1);
            }
            // Read Amount
            if (std::getline(ss, segment, ',')) {
                record.amount = std::stod(segment);
            }
        } catch (const std::exception& e) {
            record.is_valid = false; // Mark record as malformed/corrupted
        }

        return record;
    }

    // Filter records using a generic predicate/lambda
    template <typename Predicate>
    static std::vector<SalesRecord> filter(const std::vector<SalesRecord>& data, Predicate pred) {
        std::vector<SalesRecord> filtered_result;
        std::copy_if(data.begin(), data.end(), std::back_inserter(filtered_result), pred);
        return filtered_result;
    }

    // Aggregation Structure
    struct CategorySummary {
        double total_amount = 0.0;
        int count = 0;
        double average_amount() const { return count > 0 ? total_amount / count : 0.0; }
    };

    // Group by category and compute aggregations (Totals & Averages)
    static std::unordered_map<std::string, CategorySummary> aggregate_by_category(const std::vector<SalesRecord>& data) {
        std::unordered_map<std::string, CategorySummary> summary_map;
        for (const auto& record : data) {
            if (!record.is_valid) continue;

            auto& summary = summary_map[record.category];
            summary.total_amount += record.amount;
            summary.count += 1;
        }
        return summary_map;
    }
};

// ==========================================
// Example Usage: Processing Raw Sales Data
// ==========================================
int main() {
    // Simulated raw incoming dataset (CSV format: ID, Category, Amount)
    std::vector<std::string> raw_data = {
        "101, Electronics, 299.99",
        "102, Clothing, 49.50",
        "103, Electronics, 150.00",
        "104, Home, 120.75",
        "105, Clothing, 89.99",
        "106, Electronics, 450.25",
        "107, Home, 30.00",
        "INVALID_ROW_DATA", // Malformed data row to test error handling
        "108, Clothing, 120.00"
    };

    std::cout << "[Step 1] Parsing raw dataset...\n";
    std::vector<SalesRecord> records;
    records.reserve(raw_data.size());

    int malformed_count = 0;
    for (const auto& line : raw_data) {
        SalesRecord rec = DataProcessor::parse_csv_line(line);
        if (rec.is_valid) {
            records.push_back(rec);
        } else {
            malformed_count++;
        }
    }
    std::cout << "Successfully parsed: " << records.size() << " records (" << malformed_count << " dropped due to corruption).\n\n";

    // [Step 2] Filter: Keep only transactions where amount > $50.00
    std::cout << "[Step 2] Filtering records (Amount > $50.00)...\n";
    auto filtered_records = DataProcessor::filter(records, [](const SalesRecord& r) {
        return r.amount > 50.00;
    });
    std::cout << "Remaining records after filtering: " << filtered_records.size() << "\n\n";

    // [Step 3] Aggregate: Group by category and compute sums/averages
    std::cout << "[Step 3] Aggregating metrics by category...\n";
    auto summaries = DataProcessor::aggregate_by_category(filtered_records);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "---------------------------------------------------\n";
    std::cout << std::left << std::setw(15) << "Category" 
              << std::right << std::setw(12) << "Transactions" 
              << std::setw(15) << "Total ($)" 
              << std::setw(15) << "Average ($)\n";
    std::cout << "---------------------------------------------------\n";

    for (const auto& [category, summary] : summaries) {
        std::cout << std::left << std::setw(15) << category 
                  << std::right << std::setw(12) << summary.count 
                  << std::setw(15) << summary.total_amount 
                  << std::setw(15) << summary.average_amount() << "\n";
    }
    std::cout << "---------------------------------------------------\n";

    return 0;
}