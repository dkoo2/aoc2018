#include "grid.h"

#include <iostream>
#include <regex>
#include <span>
#include <string>

namespace aoc2018 {

Grid::Grid(std::span<const std::string> lines) {
    coordinates_.reserve(lines.size());
    std::regex matcher("([0-9]+), ([0-9]+)");
    int uid = 0;
    for (const std::string& l : lines) {
        std::smatch match;
        if (std::regex_search(l.begin(), l.end(), match, matcher)) {
            coordinates_.push_back(Coordinate{.uid = uid++,
                                              .row = std::stoi(match[1]),
                                              .col = std::stoi(match[2])});
        }
    }
}

int Grid::FindLargest() const {
    for (const Coordinate& coordinate : coordinates_) {
        std::cout << coordinate.uid << " " << coordinate.row << " "
                  << coordinate.col << std::endl;
    }
    return 0;
}

}  // namespace aoc2018
