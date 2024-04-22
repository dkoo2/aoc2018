#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "state.h"

int main(int argc, char* argv[]) {
    std::string initial_state;
    getline(std::cin, initial_state);

    // Read blank.
    std::string _;
    getline(std::cin, _);

    std::vector<std::string> rules;
    while (true) {
        std::string line;
        getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        rules.push_back(line);
    }
    auto start = std::chrono::system_clock::now();
    aoc2018::Generator gen(initial_state, rules);
    const int64_t res = gen.PlayTimes(50000000000);
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << res << " processing time (ms) " << elapsed.count()
              << std::endl;

    return 0;
}