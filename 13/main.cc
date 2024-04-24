#include <chrono>
#include <iostream>

#include "track.h"

int main(int argc, char* argv[]) {
    std::vector<std::string> paths;
    while (true) {
        std::string line;
        getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        paths.push_back(line);
    }

    aoc2018::Track track(paths);
    // const aoc2018::Position p = track.FirstCollision();
    // std::cout << p.col << ", " << p.row << std::endl;
    auto start = std::chrono::system_clock::now();
    const aoc2018::Position l = track.LastRemaining();
    auto end = std::chrono::system_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << l.col << ", " << l.row << " elapsed time (ms) "
              << elapsed.count() << std::endl;
    return 0;
}