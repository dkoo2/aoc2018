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
    aoc2018::Grid grid(input);
    std::cout << grid.FindLargest() << std::endl;

    return 0;
}
