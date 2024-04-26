#include <vector>

namespace aoc2018 {

class Scoreboard {
   public:
    explicit Scoreboard(int num_recipes) : max_(num_recipes) {
        recipes_.reserve(num_recipes);
        recipes_.push_back(3);
        recipes_.push_back(7);

        p1_index_ = 0;
        p2_index_ = 1;

        std::vector<int> scratch;
        scratch.reserve(6);
        int max_cpy = max_;
        while (max_cpy > 0) {
            scratch.push_back(max_cpy % 10);
            max_cpy /= 10;
        }
        max_digits_.reserve(6);
        for (int i = scratch.size() - 1; i >= 0; --i) {
            max_digits_.push_back(scratch[i]);
        }
    }

    void Make();

    int64_t PlayTimes();

    int64_t RequiredRecipes();

   private:
    int max_;
    std::vector<int> max_digits_;
    std::vector<int> recipes_;

    int64_t p1_index_;
    int64_t p2_index_;
};

}  // namespace aoc2018