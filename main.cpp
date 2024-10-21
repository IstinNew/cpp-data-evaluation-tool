#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>

// Function to read data from a CSV file
std::vector<double> read_csv(const std::string& file_name) {
    // Open the CSV file
    std::ifstream file(file_name);
    std::vector<double> data;
    std::string line, value;

    // Skip the header line
    std::getline(file, line);

    // Read each line from the CSV file
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        // Read each value separated by a comma
        while (std::getline(ss, value, ',')) {
            try {
                // Convert string to double and add to the data vector
                data.push_back(std::stod(value));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument: " << value << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range: " << value << std::endl;
            }
        }
    }
    return data;
}

// Function to calculate the mean of the data
double mean(const std::vector<double>& data) {
    double sum = 0.0;
    for (double val : data) {
        sum += val;
    }
    return sum / data.size();
}

// Function to calculate the median of the data
double median(std::vector<double> data) {
    std::sort(data.begin(), data.end()); // Sort the data
    int n = data.size();
    if (n % 2 == 0) {
        // If even number of elements, average the middle two
        return (data[n / 2 - 1] + data[n / 2]) / 2;
    } else {
        // If odd number of elements, return the middle one
        return data[n / 2];
    }
}

// Function to calculate the mode of the data
double mode(const std::vector<double>& data) {
    std::unordered_map<double, int> frequency;
    for (double val : data) {
        frequency[val]++; // Count the frequency of each value
    }
    // Find the value with the highest frequency
    return std::max_element(frequency.begin(), frequency.end(),
                            [](const auto& a, const auto& b) { return a.second < b.second; })->first;
}

int main() {
    // Specify the CSV file name
    std::string file_name = "data.csv";

    // Read data from the CSV file
    std::vector<double> data = read_csv(file_name);

    // Calculate and display mean, median, and mode
    if (!data.empty()) {
        std::cout << "Mean: " << mean(data) << std::endl;
        std::cout << "Median: " << median(data) << std::endl;
        std::cout << "Mode: " << mode(data) << std::endl;
    } else {
        std::cerr << "Error: No valid data found in the file." << std::endl;
    }

    return 0;
}