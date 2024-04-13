#include <chrono>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "grid.h"

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
    int part_1 = -1;
    int part_2 = -1;
    auto p1_start = std::chrono::system_clock::now();
    aoc2018::Grid grid(input);
    part_1 = grid.FindLargest();
    auto p1_end = std::chrono::system_clock::now();
    auto p1_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        p1_end - p1_start);

    auto p2_start = std::chrono::system_clock::now();
    part_2 = grid.CommonLeast();
    auto p2_end = std::chrono::system_clock::now();
    auto p2_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        p2_end - p2_start);
    std::cout << part_1 << " " << part_2 << " -- Part 1 total time (ms) "
              << p1_elapsed.count() << " -- Part 2 total time (ms) "
              << p2_elapsed.count() << std::endl;

    return 0;
}
