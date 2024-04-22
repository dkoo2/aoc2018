#include <array>
#include <deque>
#include <map>
#include <span>
#include <string>

namespace aoc2018 {

struct Cell {
    int val;
    int index;
};

class Generator {
   public:
    Generator(const std::string& initial_state,
              std::span<const std::string> rules);

    int64_t PlayTimes(int64_t n);

   private:
    void PlayOnce();
    void Print() const;
    std::deque<Cell> states_;
    std::map<std::array<int, 5>, int> rules_;

    int prev_sum_ = 0;
    int prev_diff_ = INT_MAX;
};

}  // namespace aoc2018