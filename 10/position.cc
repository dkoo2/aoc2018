#include "position.h"

#include <iostream>
#include <regex>
#include <string>

namespace aoc2018 {

void Point::RunOnce() {
    px_ += vx_;
    py_ += vy_;
}

Grid::Grid(std::span<const std::string> lines) {
    points_.reserve(lines.size());
    std::regex matcher("position=<(.*), (.*)> velocity=<(.*),(.*)>");
    for (const std::string& l : lines) {
        std::smatch match;
        if (std::regex_search(l.begin(), l.end(), match, matcher)) {
            points_.emplace_back(std::stoi(match[1]), std::stoi(match[2]),
                                 std::stoi(match[3]), std::stoi(match[4]));
        }
    }
}

void Grid::RunOnce() {
    for (Point& p : points_) {
        p.RunOnce();
    }
}

int Grid::RunUntilConnected() {
    int timer = 0;
    do {
        ++timer;
        RunOnce();
    } while (!Connected());
    return timer;
}

bool Grid::Connected() const {
    static constexpr std::array<std::pair<int, int>, 8> directions = {
        {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}};
    for (const Point& p : points_) {
        bool hs_neighbor = false;
        for (const std::pair<int, int>& dir : directions) {
            for (const Point& np : points_) {
                if (np.px() == p.px() + dir.first &&
                    np.py() == p.py() + dir.second) {
                    hs_neighbor = true;
                    break;
                }
            }
        }
        if (!hs_neighbor) {
            return false;
        }
    }
    return true;
}

void Grid::Print() const {
    int max_x = -1;
    int min_x = INT_MAX;
    int max_y = -1;
    int min_y = INT_MAX;
    for (const Point& p : points_) {
        if (p.px() > max_x) {
            max_x = p.px();
        }
        if (p.px() < min_x) {
            min_x = p.px();
        }
        if (p.py() > max_y) {
            max_y = p.py();
        }
        if (p.py() < min_y) {
            min_y = p.py();
        }
    }
    for (int y = min_y; y <= max_y; ++y) {
        for (int x = min_x; x <= max_x; ++x) {
            bool has_point = false;
            for (const Point& p : points_) {
                if (p.px() == x && p.py() == y) {
                    has_point = true;
                    break;
                }
            }
            if (has_point) {
                std::cout << "#";
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
}  // namespace aoc2018