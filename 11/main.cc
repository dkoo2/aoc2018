#include <chrono>
#include <iostream>
#include <utility>

#include "grid.h"

int main(int argc, char* argv[]) {
    aoc2018::Grid grid(9435);
    const std::pair<int, int> largest3x3 = grid.Largest3x3();
    std::cout << largest3x3.first << " " << largest3x3.second << std::endl;

    auto start = std::chrono::system_clock::now();
    const std::tuple<int, int, int> largest_any = grid.Largest();
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << std::get<0>(largest_any) << "," << std::get<1>(largest_any)
              << "," << std::get<2>(largest_any) << " total time spend (ms) "
              << elapsed.count() << std::endl;

    return 0;
}