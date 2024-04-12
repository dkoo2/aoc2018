#include <cassert>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <span>

std::pair<bool, bool> DupCount(std::string_view line) {
    std::map<char, int> counter;
    std::for_each(line.begin(), line.end(), [&](char c) { counter[c]++; });
    bool has_two = false;
    bool has_three = false;
    for (const auto& [_, count] : counter) {
        if (count == 2) {
            has_two = true;
        }
        if (count == 3) {
            has_three = true;
        }
    }
    return std::make_pair(has_two, has_three);
}

std::string FindDiffByOne(std::span<const std::string> inputs) {
    for (int i = 0; i < inputs.size(); ++i) {
        for (int j = i + 1; j < inputs.size(); ++j) {
            assert(inputs[i].size() == inputs[j].size());
            int diff = 0;
            int diff_index = -1;
            for (int s = 0; s < inputs[i].size(); ++s) {
                if (inputs[i][s] != inputs[j][s]) {
                    diff_index = s;
                    ++diff;
                }
                if (diff >= 2) {
                    break;
                }
            }
            if (diff == 1) {
                std::cout << inputs[i] << " && " << inputs[j] << std::endl;

                return inputs[i].substr(0, diff_index) + inputs[i].substr(diff_index + 1);
            }
        }
    }
    return "";
}

// Program entry point.
// Reads infile and parses the text.
int main() {
    std::vector<std::string> input;
    while (true) {
        std::string line;
        std::cin >> line;
        if (line.empty()) {
            break;
        }
        input.push_back(line);
    }
    int twos = 0;
    int threes = 0;
    for (std::string_view line : input) {
        std::pair<bool, bool> res = DupCount(line);
        if (res.first) {
            ++twos;
        }
        if (res.second) {
            ++threes;
        }
    }
    std::cout << twos * threes << std::endl;

    std::cout << FindDiffByOne(input) << std::endl;

    return 0;
}

