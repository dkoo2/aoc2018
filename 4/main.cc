#include <chrono>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "sleep_study.h"

// Program entry point.
// Reads infile and parses the text.
int main(int argc, char* argv[]) {
    std::vector<std::string> input;
    while (true) {
        std::string line;
        getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        input.push_back(line);
    }

    auto start = std::chrono::system_clock::now();
    aoc2018::SleepStudy sleep_study_in(input);
    const std::pair<int, int> strategy = sleep_study_in.Strategy();
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << strategy.first << " " << strategy.second << " in time (ms) "
              << elapsed.count() << std::endl;

    return 0;
}
