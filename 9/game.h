#pragma once

#include <list>
#include <vector>

namespace aoc2018 {

class Game {
   public:
    explicit Game(int players, int last_marble)
        : players_(players), last_marble_(last_marble) {
        player_scores_.resize(players_);
        board_.insert(board_.begin(), 0);
        curr_ = board_.begin();
        next_marble_ = 1;
        curr_player_ = 1;
    }

    int64_t HighScore();

   private:
    int players_;
    int curr_player_;
    const int last_marble_;
    int next_marble_;

    // Rightwards is clockwise.
    std::list<int> board_;
    std::list<int>::iterator curr_;

    // Index 0 is invalid by convention.
    std::vector<int64_t> player_scores_;
};

}  // namespace aoc2018
