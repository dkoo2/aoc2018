#include "grid.h"

#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

namespace aoc2018 {

std::pair<int, int> Grid::Largest3x3() const {
    const std::tuple<int, int, int> f3x3 = LargestForDim(3);
    return std::make_pair(std::get<0>(f3x3), std::get<1>(f3x3));
}

std::tuple<int, int, int> Grid::LargestForDim(const int dim) const {
    int curr_max = -1;
    std::pair<int, int> max_pair = {-1, -1};
    for (int i = dim; i < 300; ++i) {
        for (int j = dim; j < 300; ++j) {
            const int d = summed_fuels_[i][j];
            const int a = summed_fuels_[i - dim][j - dim];
            const int c = summed_fuels_[i][j - dim];
            const int b = summed_fuels_[i - dim][j];
            const int curr = d + a - c - b;
            if (curr_max < curr) {
                curr_max = curr;
                max_pair = {j - dim + 1, i - dim + 1};
            }
        }
    }
    return std::make_tuple(max_pair.first + 1, max_pair.second + 1, curr_max);
}

std::tuple<int, int, int> Grid::Largest() const {
    std::vector<std::thread> threads;
    constexpr int num_threads = 12;
    threads.reserve(num_threads);

    std::atomic<int> curr_max(-1);
    std::atomic<int> curr_max_s(-1);
    struct CMPair {
        int x;
        int y;
    };
    std::atomic<CMPair> curr_max_pair({-1, -1});
    for (int t_num = 0; t_num < num_threads; ++t_num) {
        threads.emplace_back(
            std::thread([this, t_num, &curr_max, &curr_max_s, &curr_max_pair] {
                int start = 2 + t_num;
                for (int s = start; s <= 300; s += num_threads) {
                    std::tuple<int, int, int> max_s = LargestForDim(s);
                    if (std::get<2>(max_s) > curr_max) {
                        {
                            curr_max.store(std::get<2>(max_s),
                                           std::memory_order_relaxed);
                            curr_max_s.store(s, std::memory_order_relaxed);
                            curr_max_pair.store(
                                {std::get<0>(max_s), std::get<1>(max_s)},
                                std::memory_order_relaxed);
                        }
                    }
                }
            }));
    }
    for (int i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }
    const int max_x = curr_max_pair.load(std::memory_order_relaxed).x;
    const int max_y = curr_max_pair.load(std::memory_order_relaxed).y;
    const int max_s = curr_max_s.load(std::memory_order_relaxed);
    return std::make_tuple(max_x, max_y, max_s);
}

void Grid::Initialize() {
    fuel_cells_.reserve(300);
    for (int i = 0; i < 300; ++i) {
        std::vector<int> curr;
        curr.reserve(300);
        for (int j = 0; j < 300; ++j) {
            const int x = j + 1;
            const int y = i + 1;
            const int rack_id = x + 10;

            int power_level = rack_id * y;
            power_level += serial_num_;
            power_level *= rack_id;

            if (power_level < 100) {
                power_level = 0;
            } else {
                power_level /= 100;
                power_level %= 10;
            }
            power_level -= 5;
            curr.push_back(power_level);
        }
        fuel_cells_.push_back(std::move(curr));
    }
    summed_fuels_.reserve(300);
    for (int i = 0; i < 300; ++i) {
        std::vector<int> r(300, 0);
        summed_fuels_.push_back(std::move(r));
    }
    for (int i = 0; i < 300; ++i) {
        for (int j = 0; j < 300; ++j) {
            summed_fuels_[i][j] = fuel_cells_[i][j];
            if (i > 1) {
                summed_fuels_[i][j] += summed_fuels_[i - 1][j];
            }
            if (j > 1) {
                summed_fuels_[i][j] += summed_fuels_[i][j - 1];
            }
            if (i > 1 && j > 1) {
                summed_fuels_[i][j] -= summed_fuels_[i - 1][j - 1];
            }
        }
    }
}

}  // namespace aoc2018