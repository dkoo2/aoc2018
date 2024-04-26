#include <chrono>
#include <iostream>

#include "scoreboard.h"

int main(int argc, char* argv[]) {
    aoc2018::Scoreboard sb(323081);
    auto start = std::chrono::system_clock::now();
    const int64_t rr = sb.RequiredRecipes();
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << rr << " elapsed time (milliseconds) " << elapsed.count()
              << std::endl;

    return 0;
}