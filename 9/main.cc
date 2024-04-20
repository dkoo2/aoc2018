#include <chrono>
#include <iostream>

#include "game.h"

int main(int argc, char* argv[]) {
    aoc2018::Game game(423, 7194400);

    auto start = std::chrono::system_clock::now();
    const int64_t part_2 = game.HighScore();
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << part_2 << " elapsed time (ms) : " << elapsed.count()
              << std::endl;
    return 0;
}
