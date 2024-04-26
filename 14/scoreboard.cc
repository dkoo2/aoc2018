#include "scoreboard.h"

#include <iostream>
#include <span>
#include <vector>

namespace aoc2018 {

void Scoreboard::Make() {
    const int curr_p1 = recipes_[p1_index_];
    const int curr_p2 = recipes_[p2_index_];

    int new_r = curr_p1 + curr_p2;

    if (new_r < 10) {
        recipes_.push_back(new_r);
    } else {
        const int ld = new_r % 10;
        new_r /= 10;
        const int fd = new_r % 10;
        recipes_.push_back(fd);
        recipes_.push_back(ld);
    }
    p1_index_ = (p1_index_ + 1 + curr_p1) % (recipes_.size());
    p2_index_ = (p2_index_ + 1 + curr_p2) % (recipes_.size());
}

int64_t Scoreboard::PlayTimes() {
    while (recipes_.size() < max_ + 10) {
        Make();
    }
    int64_t sum = 0;
    for (int i = max_; i <= max_ + 9; ++i) {
        sum += (recipes_[i] * (10 ^ (max_ + 9 - i)));
    }
    return sum;
}

namespace {

bool Match(std::span<const int> recipes, const size_t start_index,
           std::span<const int> comp) {
    for (int i = 0; i < comp.size(); ++i) {
        if (recipes[i + start_index] != comp[i]) {
            return false;
        }
    }
    return true;
}

}  // namespace

int64_t Scoreboard::RequiredRecipes() {
    size_t start_index = 0;
    for (;;) {
        while (recipes_.size() <= start_index + 100) {
            Make();
        }
        // Check if we have our number.
        if (Match(recipes_, start_index, max_digits_)) {
            return start_index;
        }
        ++start_index;
    }

    __builtin_unreachable();
    return 0;
}

}  // namespace aoc2018