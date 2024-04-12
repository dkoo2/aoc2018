#include <cassert>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>

// Program entry point.
// Reads infile and parses the text.
int main() {
    std::ifstream input;
    const std::string filepath = 
        "/Users/fatpeasant/experiments/aoc2018/1/infile.txt";
    input.open(filepath);
    assert(input.is_open());
    std::vector<std::string> strings;
    std::string line;
    while (input) {
        getline(input, line);
        strings.push_back(line);
    }
    input.close();

    int sum = 0;
    std::set<int> seen;
    while (true) {
        bool found = false;
        for (int i = 0; i < strings.size() - 1; ++i) {
            sum += std::stoi(strings[i]);
            if (seen.contains(sum)) {
                std::cout << "Found: " << sum << std::endl;
                found = true;
                break;
            }
            seen.insert(sum);
        }
        if (found) break;
    }
    return 0;
}
