#include <chrono>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "dependency.h"

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

    // Get results.
    auto start = std::chrono::system_clock::now();
    aoc2018::Graph graph(input);
    const std::vector<int> res = graph.FindOrder();
    int part_2 = graph.TimeConsumed(res);
    auto end = std::chrono::system_clock::now();

    // Print results and time taken.
    for (const int r : res) {
        std::string s(1, char(r + 65));
        std::cout << s;
    }
    std::cout << std::endl;
    std::cout << part_2 << std::endl;
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken (microseconds) : " << elapsed.count() << std::endl;
    return 0;
}
