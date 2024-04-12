#include "grid.h"

#include <cassert>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <span>
#include <string>
#include <utility>

namespace aoc2018 {

Grid::Grid(std::span<const std::string> lines) {
    std::regex matcher("#([0-9]+) @ ([0-9]+),([0-9]+): ([0-9]+)x([0-9]+)");
    for (const std::string& l : lines) {
        std::smatch match;
        if (std::regex_search(l.begin(), l.end(), match, matcher)) {
            fills_.push_back(Fill{.id = std::stoi(match[1]),
                                  .left_offset = std::stoi(match[2]),
                                  .top_offset = std::stoi(match[3]),
                                  .width = std::stoi(match[4]),
                                  .height = std::stoi(match[5])});
        }
    }
}

int Grid::Overlaps() const {
    std::map<std::pair<int, int>, int> counter;
    for (const Fill& fill : fills_) {
        for (int row = fill.top_offset; row < fill.top_offset + fill.height;
             ++row) {
            for (int col = fill.left_offset;
                 col < fill.left_offset + fill.width; ++col) {
                ++counter[std::make_pair(row, col)];
            }
        }
    }
    int dups = 0;
    for (const auto& [_, count] : counter) {
        if (count >= 2) {
            ++dups;
        }
    }
    return dups;
}

int Grid::Intact() const {
    std::map<std::pair<int, int>, std::set<int>> mappings;
    std::set<int> all;
    for (const Fill& fill : fills_) {
        all.insert(fill.id);
        for (int row = fill.top_offset; row < fill.top_offset + fill.height;
             ++row) {
            for (int col = fill.left_offset;
                 col < fill.left_offset + fill.width; ++col) {
                const auto p = std::make_pair(row, col);
                mappings[p].insert(fill.id);
            }
        }
    }
    for (const auto& [_, ids] : mappings) {
        if (ids.size() > 1) {
            for (const int id : ids) {
                all.erase(id);
            }
        }
    }
    assert(all.size() == 1);
    return *all.begin();
}

}  // namespace aoc2018
