#include "grid.h"

#include <atomic>
#include <cassert>
#include <iostream>
#include <map>
#include <regex>
#include <span>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>

namespace aoc2018 {

Grid::Grid(std::span<const std::string> lines) {
    coordinates_.reserve(lines.size());
    std::regex matcher("([0-9]+), ([0-9]+)");
    int uid = 0;
    for (const std::string& l : lines) {
        std::smatch match;
        if (std::regex_search(l.begin(), l.end(), match, matcher)) {
            const int row = std::stoi(match[1]);
            const int col = std::stoi(match[2]);
            coordinates_.push_back(
                Coordinate{.uid = uid++, .row = row, .col = col});
            row_max_ = std::max(row_max_, row);
            col_max_ = std::max(col_max_, col);
        }
    }
    max_uid_ = uid - 1;
}

namespace {

int ManhattanDistance(const std::pair<int, int>& target,
                      const Coordinate& coordinate) {
    return std::abs(target.first - coordinate.row) +
           std::abs(target.second - coordinate.col);
}

}  // namespace

int Grid::FindLargest() const {
    std::vector<std::vector<int>> min_dist;
    min_dist.reserve(row_max_ + 1);
    for (int i = 0; i <= row_max_; ++i) {
        std::vector<int> c(col_max_ + 1, INT_MAX);
        min_dist.push_back(std::move(c));
    }

    std::map<std::pair<int, int>, std::unordered_set<int>>
        coordinates_to_min_id;
    for (int i = 0; i <= row_max_; ++i) {
        for (int j = 0; j <= col_max_; ++j) {
            for (const Coordinate& coordinate : coordinates_) {
                const auto target = std::make_pair(i, j);
                const int dist = ManhattanDistance(target, coordinate);
                if (min_dist[i][j] > dist) {
                    min_dist[i][j] = dist;
                    coordinates_to_min_id[target] = {coordinate.uid};
                } else if (min_dist[i][j] == dist) {
                    coordinates_to_min_id[target].insert(coordinate.uid);
                }
            }
        }
    }

    std::vector<bool> infinite_uids(max_uid_ + 1, false);
    for (const auto& [coordinate, ids] : coordinates_to_min_id) {
        if ((coordinate.first == 0 || coordinate.second == 0 ||
             coordinate.first == row_max_ || coordinate.second == col_max_) &&
            ids.size() == 1) {
            infinite_uids[*ids.begin()] = true;
        }
    }

    std::unordered_map<int, int> id_to_count;
    for (const auto& [_, ids] : coordinates_to_min_id) {
        if (ids.size() != 1) {
            continue;
        }
        const int id = *ids.begin();
        if (!infinite_uids[id]) {
            ++id_to_count[id];
        }
    }
    int largest = -1;
    for (const auto& [id, count] : id_to_count) {
        largest = std::max(largest, count);
    }

    return largest;
}

namespace {

bool AllIsLessThan(const std::vector<Coordinate>& coordinates,
                   const std::pair<int, int>&& target) {
    int total_dist = 0;
    for (const Coordinate& coordinate : coordinates) {
        total_dist += ManhattanDistance(target, coordinate);
        if (total_dist >= 10000) {
            return false;
        }
    }
    return true;
}

}  // namespace

int Grid::CommonLeast() const {
    std::atomic<int> good(0);
    constexpr int num_threads = 12;
    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    for (int t_num = 0; t_num < num_threads; ++t_num) {
        threads.emplace_back(std::thread([this, t_num, &good]() {
            const int start_row = t_num;
            for (int i = start_row; i <= row_max_; i += num_threads) {
                for (int j = 0; j <= col_max_; ++j) {
                    if (AllIsLessThan(coordinates_, std::make_pair(i, j))) {
                        good.fetch_add(1, std::memory_order_relaxed);
                    }
                }
            }
        }));
    }
    for (int i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }
    return good;
}

}  // namespace aoc2018
