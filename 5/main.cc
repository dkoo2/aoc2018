#include <chrono>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "polymer.h"

// Program entry point.
// Reads infile and parses the text.
int main(int argc, char* argv[]) {
    std::string input;
    getline(std::cin, input);

    aoc2018::Polymer polymer(input);
    auto start = std::chrono::system_clock::now();
    int part_1 = polymer.Collapse();
    int part_2 = polymer.ShortestAfterRemoval();
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << part_1 << std::endl;
    std::cout << part_2 << std::endl;
    std::cout << "Total time (ms) : " << elapsed.count() << std::endl;
    return 0;
}
