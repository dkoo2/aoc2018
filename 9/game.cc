#include "game.h"

#include <iostream>

namespace aoc2018 {

namespace {

int NextPlayer(const int next_player, const int players) {
    return next_player > players ? 1 : next_player;
}

}  // namespace

int64_t Game::HighScore() {
    for (;;) {
        if (next_marble_ > last_marble_) {
            break;
        }

        if (board_.size() < 2) {
            curr_ = board_.insert(++curr_, next_marble_++);
            curr_player_ = NextPlayer(curr_player_ + 1, players_);
            continue;
        }

        if (next_marble_ % 23 != 0) {
            if (std::next(curr_) == board_.end()) {
                curr_ = board_.begin();
            } else {
                ++curr_;
            }
            curr_ = board_.insert(++curr_, next_marble_++);
            curr_player_ = NextPlayer(curr_player_ + 1, players_);
            continue;
        }
        // Multiple of 23.
        // The current player keeps the current marble.
        player_scores_[curr_player_] += next_marble_++;

        // Find the marble that is 7 units counter clockwise.
        for (int i = 0; i < 7; ++i) {
            if (curr_ == board_.begin()) {
                curr_ = std::prev(board_.end());
                continue;
            }
            curr_ = std::prev(curr_);
        }
        player_scores_[curr_player_] += *curr_;
        curr_ = board_.erase(curr_);
        curr_player_ = NextPlayer(curr_player_ + 1, players_);
    }

    int64_t max = -1;
    for (const int64_t score : player_scores_) {
        if (score > max) {
            max = score;
        }
    }
    return max;
}

}  // namespace aoc2018