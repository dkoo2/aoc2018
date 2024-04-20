#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "position.h"

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
    aoc2018::Grid grid(input);
    int timer = grid.RunUntilConnected();
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    grid.Print();
    std::cout << "Ret : " << timer
              << " time consumed (ms) : " << elapsed.count() << std::endl;
    return 0;
}
