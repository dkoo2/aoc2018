#include "state.h"

#include <cassert>
#include <regex>
#include <span>
#include <string>
#include <iostream>

namespace aoc2018 {

namespace {

int ToInt(std::string_view s) {
    assert(s == "#" || s == ".");
    if (s == "#") {
        return 1;
    }
    return 0;
}

std::array<int, 5> ToIntArray(std::string_view key) {
    assert(key.size() == 5);
    std::array<int, 5> ret = {0, 0, 0, 0, 0};
    for (int i = 0; i < key.size(); ++i) {
        if (key.substr(i, 1) == "#") {
            ret[i] = 1;
        }
    }
    return ret;
}

int First(const std::deque<Cell>& states) {
    for (int i = 0; i < states.size(); ++i) {
        if (states[i].val == 1) {
            return i + 1;
        }
    }
    assert(false);
    return states.size();
}

int Last(const std::deque<Cell>& states) {
    for (int i = 1; i <= states.size(); ++i) {
        if (states[states.size() - i].val == 1) {
            return i;
        }
    }
    assert(false);
    return states.size();
}

int StatesSum(const std::deque<Cell>& states) {
    int sum = 0;
    for (int i = 0; i < states.size(); ++i) {
        if (states[i].val == 1) {
            sum += states[i].index;
        }
    }
    return sum;
}

}  // namespace

void Generator::Print() const {
    for (int i = 0; i < states_.size(); ++i) {
        std::cout << states_[i].val << "(idx" << states_[i].index << ") ";
    }
    std::cout << std::endl;
}

int64_t Generator::PlayTimes(const int64_t n) {
    for (int64_t i = 0; i < n; ++i) {
        PlayOnce();
        const int sum = StatesSum(states_);
        const int curr_diff = sum - prev_sum_;
        if (curr_diff == prev_diff_) {
            const int64_t future_iter = n - 1 - i;
            const int64_t mul_d = future_iter * curr_diff;
            return sum + mul_d;
        }
        prev_sum_ = sum;
        prev_diff_ = curr_diff;
    }
    return prev_sum_;
}

void Generator::PlayOnce() {
    const int distance_to_first = First(states_);

    if (distance_to_first <= 5) {
        const int front_index = states_[0].index;
        for (int i = 1; i < 6; ++i) {
            states_.push_front({0, front_index - i});
        }
    }

    const int distance_from_last = Last(states_);
    if (distance_from_last <= 5) {
        const int back_index = states_.back().index;
        for (int i = 1; i < 6; ++i) {
            states_.push_back({0, back_index + i});
        }
    }

    std::deque<Cell> new_processing;
    new_processing.push_back(states_[0]);
    new_processing.push_back(states_[1]);

    for (int i = 2; i <= states_.size() - 3; ++i) {
        std::array<int, 5> processing = {states_[i - 2].val, states_[i - 1].val,
                                         states_[i].val, states_[i + 1].val,
                                         states_[i + 2].val};
        if (rules_[processing] == 0) {
            new_processing.push_back({0, states_[i].index});
            continue;
        }
        new_processing.push_back({1, states_[i].index});
    }
    new_processing.push_back({0, states_[states_.size() - 2].index});
    new_processing.push_back({0, states_[states_.size() - 1].index});

    states_ = std::move(new_processing);
}

Generator::Generator(const std::string& initial_state,
                     std::span<const std::string> rules) {
    std::regex init_state_matcher("initial state: ([#|.]+).*");
    std::smatch state_matcher;
    const bool init_state_match =
        std::regex_search(initial_state.begin(), initial_state.end(),
                          state_matcher, init_state_matcher);
    if (!init_state_match) {
        std::exit(-1);
    }
    const std::string init_state = state_matcher[1];
    for (int i = 0; i < init_state.size(); ++i) {
        states_.push_back({ToInt(init_state.substr(i, 1)), i});
    }
    std::regex matcher("(.*) => (#|.)");
    for (const std::string& r : rules) {
        std::smatch match;
        if (std::regex_search(r.begin(), r.end(), match, matcher)) {
            const std::string k = match[1];
            const std::string v = match[2];
            rules_[ToIntArray(k)] = ToInt(v);
        }
    }
}

}  // namespace aoc2018