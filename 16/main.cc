#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "classifier.h"

int main(int argc, char* argv[]) {
    std::vector<std::vector<std::string>> inputs;
    std::vector<std::string> first;
    inputs.push_back(first);
    bool prev_line_empty = false;
    for (;;) {
        std::string line;
        getline(std::cin, line);
        if (line.empty()) {
            if (prev_line_empty) {
                break;
            }
            prev_line_empty = true;
            // New vector.
            std::vector<std::string> v;
            v.reserve(3);
            inputs.push_back(std::move(v));
            continue;
        }
        prev_line_empty = false;
        inputs.back().push_back(line);
    }

    // Start reading the instructions as well.
    std::vector<std::string> instructions;
    for (;;) {
        std::string line;
        getline(std::cin, line);
        if (!std::cin) {
            break;
        }
        instructions.push_back(line);
    }

    aoc2018::Classifier classifier(inputs, instructions);
    auto start = std::chrono::system_clock::now();
    int p2 = classifier.Part2();
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << p2 << " , time elapsed (microseconds) " << elapsed.count() << std::endl;
    return 0;
}