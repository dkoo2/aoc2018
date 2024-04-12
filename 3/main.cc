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

    aoc2018::Grid grid(input);
    std::cout << grid.Overlaps() << std::endl;

    std::cout << grid.Intact() << std::endl;

    return 0;
}
