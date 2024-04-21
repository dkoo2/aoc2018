#include <vector>

namespace aoc2018 {

class Grid {
   public:
    explicit Grid(int serial_num) : serial_num_(serial_num) { Initialize(); }

    std::pair<int, int> Largest3x3() const;

    // Returns <i, j, square_size>
    std::tuple<int, int, int> Largest() const;

    // Returns <i, j, max>
    std::tuple<int, int, int> LargestForDim(int dim) const;

   private:
    void Initialize();
    const int serial_num_;

    std::vector<std::vector<int>> fuel_cells_;
    std::vector<std::vector<int>> summed_fuels_;
};

}  // namespace aoc2018
