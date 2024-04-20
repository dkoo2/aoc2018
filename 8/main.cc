#include <chrono>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "node.h"

int main(int argc, char* argv[]) {
    std::vector<std::string> input;
    while (true) {
        std::string line;
        std::cin >> line;
        if (line.empty()) {
            break;
        }
        input.push_back(line);
    }
    auto start = std::chrono::system_clock::now();
    const aoc2018::Root root(input);
    const int part_1 = root.MetadataSum();
    const int part_2 = root.IndexedSum();
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << part_1 << " " << part_2
              << " in elapsed time (microseconds) : " << elapsed.count()
              << std::endl;
    return 0;
}
