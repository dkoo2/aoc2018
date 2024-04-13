#include "polymer.h"

#include <atomic>
#include <iostream>
#include <memory>
#include <thread>

namespace aoc2018 {

Polymer::Polymer(std::string_view line) {
    ascii_.reserve(line.size());
    for (int i = 0; i < line.size(); ++i) {
        ascii_.push_back(static_cast<int>(line[i]));
    }
}

namespace {

bool Reacts(int lhs, int rhs) { return std::abs(lhs - rhs) == 32; }

std::vector<int> Remove(const std::vector<int>& ascii, const int upper,
                        const int lower) {
    std::vector<int> cpy = ascii;
    for (int i = 0; i < cpy.size(); ++i) {
        if (cpy[i] == upper || cpy[i] == lower) {
            cpy[i] = INT_MAX;
        }
    }
    return cpy;
}

int FindNextNonMax(const std::vector<int>& ascii, int i) {
    for (int index = i + 1; index <= ascii.size(); ++index) {
        if (ascii[index] != INT_MAX) {
            return index;
        }
    }
    return -1;
}

int FindPrevNonMax(const std::vector<int>& ascii, int i) {
    for (int index = i - 1; i >= 0; --index) {
        if (ascii[index] != INT_MAX) {
            return index;
        }
    }
    return -1;
}

}  // namespace

int Polymer::Collapse() const {
    int changed = 0;
    std::vector<int> ascii_cpy = ascii_;
    do {
        changed = 0;
        for (int i = 0; i < ascii_cpy.size() - 1; ++i) {
            if (ascii_cpy[i] == INT_MAX) continue;
            const int next = FindNextNonMax(ascii_cpy, i);
            if (next < 0) continue;
            if (Reacts(ascii_cpy[i], ascii_cpy[next])) {
                ++changed;
                ascii_cpy[i] = INT_MAX;
                ascii_cpy[next] = INT_MAX;
                int fpnm = FindPrevNonMax(ascii_cpy, i);
                i = fpnm - 1;
            }
        }
    } while (changed > 0);

    int count = 0;
    for (const int a : ascii_cpy) {
        if (a != INT_MAX) {
            ++count;
        }
    }
    return count;
}

int Polymer::ShortestAfterRemoval() const {
    std::vector<std::thread> threads;
    constexpr int num_threds = 12;
    threads.reserve(num_threds);
    std::atomic<int> shortest;
    shortest.store(INT_MAX, std::memory_order_relaxed);
    for (int t_num = 0; t_num < num_threds; ++t_num) {
        threads.emplace_back(std::thread([this, t_num, &shortest]() {
            const int start = 65 + t_num;
            for (int pd = start; pd <= 90; pd += num_threds) {
                const int lower = pd + 32;
                std::vector<int> ascii_remove = Remove(ascii_, pd, lower);
                int changed = 0;
                do {
                    changed = 0;
                    for (int i = 0; i < ascii_remove.size() - 1; ++i) {
                        if (ascii_remove[i] == INT_MAX) continue;
                        const int next = FindNextNonMax(ascii_remove, i);
                        if (next < 0) continue;
                        if (Reacts(ascii_remove[i], ascii_remove[next])) {
                            ++changed;
                            ascii_remove[i] = INT_MAX;
                            ascii_remove[next] = INT_MAX;
                            int fpnm = FindPrevNonMax(ascii_remove, i);
                            i = fpnm - 1;
                        }
                    }
                } while (changed > 0);

                int count = 0;
                for (const int a : ascii_remove) {
                    if (a != INT_MAX) {
                        ++count;
                    }
                }
                int curr_shortest = shortest.load(std::memory_order_relaxed);
                while (curr_shortest > count &&
                       !shortest.compare_exchange_strong(curr_shortest, count)) {
                }
            }
        }));
    }
    for (int i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }
    return shortest;
}

}  // namespace aoc2018
