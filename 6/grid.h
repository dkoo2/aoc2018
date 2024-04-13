#include <span>
#include <string>
#include <utility>
#include <vector>

namespace aoc2018 {

struct Coordinate {
    int uid;
    int row;
    int col;
};

class Grid {
   public:
    explicit Grid(std::span<const std::string> lines);

    // Part 1.
    int FindLargest() const;

    // Part 2.
    int CommonLeast() const;

   private:
    std::vector<Coordinate> coordinates_;
    int row_max_ = -1;
    int col_max_ = -1;
    int max_uid_ = -1;
};

}  // namespace aoc2018
