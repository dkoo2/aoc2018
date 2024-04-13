#include <iostream>
#include <string>
#include <vector>

#include "grid.h"

// Program entry point.
// Reads infile and parses the text.
int main() {
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
    auto start = std::chrono::system_clock::now();
    aoc2018::Grid grid(input);
    part_1 = grid.Overlaps();
    part_2 = grid.Intact();
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "1: " << part_1 << " 2: " << part_2
              << " timespent (ms) : " << elapsed.count() << std::endl;

    return 0;
}
