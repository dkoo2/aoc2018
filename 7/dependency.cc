#include "dependency.h"

#include <cassert>
#include <iostream>
#include <regex>
#include <span>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace aoc2018 {

Graph::Graph(std::span<const std::string> lines) {
    std::regex matcher(
        "Step (\\w) must be finished before step (\\w) can begin.");
    for (const std::string& l : lines) {
        std::smatch match;
        if (std::regex_search(l.begin(), l.end(), match, matcher)) {
            const std::string& first = match[1];
            const std::string& second = match[2];
            int f = first[0] - 65;
            int s = second[0] - 65;
            prereqs_[s].insert(f);
            all_.insert(f);
            all_.insert(s);
        }
    }
}

// `dependencies` maps what needs to start (key) in order for the value to also
// start.
std::vector<int> Graph::FindOrder() const {
    // Start by finding any values that do not have a dependency.
    std::vector<int> order;
    order.reserve(all_.size());

    std::unordered_set<int> finished;

    // Copy this since Part 2 needs a fresh copy too.
    std::unordered_map<int, std::unordered_set<int>> prereqs = prereqs_;
    while (order.size() < all_.size()) {
        int next_free = -1;
        for (int i = 0; i < 26; ++i) {
            if (prereqs[i].empty() && !finished.contains(i)) {
                next_free = i;
                break;
            }
        }
        order.push_back(next_free);
        finished.insert(next_free);
        for (auto& [_, d] : prereqs) {
            d.erase(next_free);
        }
    }
    return order;
}

namespace {

inline int TCost(const int element) { return element + 61; }

int Min(const std::array<std::pair<int, int>, 5>& workers) {
    int min = INT_MAX;
    for (const auto& [_, time] : workers) {
        if (time == 0) continue;
        if (time < min) {
            min = time;
        }
    }
    return min;
}

int Max(const std::array<std::pair<int, int>, 5>& workers) {
    int max = -1;
    for (const auto& [_, time] : workers) {
        if (time > max) {
            max = time;
        }
    }
    return max;
}

}  // namespace

int Graph::TimeConsumed(std::span<const int> order) {
    std::array<std::pair<int, int>, 5> workers = {
        {{-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}}};
    int time_passed = 0;

    std::unordered_set<int> processed;
    do {
        // Try enqueueing things available.
        for (int i = 0; i < 26; ++i) {
            if (prereqs_[i].empty() && !processed.contains(i)) {
                // Try running.
                for (std::pair<int, int>& worker : workers) {
                    if (worker.second == 0) {
                        worker.first = i;
                        worker.second = TCost(i);
                        processed.insert(i);
                        break;
                    }
                }
            }
        }
        // Pass time by minimum time remaining.
        const int min_remaining = Min(workers);
        time_passed += min_remaining;
        for (std::pair<int, int>& worker : workers) {
            if (worker.second == 0) {
                continue;
            }
            worker.second -= min_remaining;
            if (worker.second == 0) {
                for (auto& [_, d] : prereqs_) {
                    d.erase(worker.first);
                }
            }
        }
    } while (processed.size() < all_.size());

    return time_passed + Max(workers);
}

}  // namespace aoc2018
