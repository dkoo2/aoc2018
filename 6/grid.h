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

    int FindLargest() const;

   private:
    std::vector<Coordinate> coordinates_;
};

}  // namespace aoc2018
