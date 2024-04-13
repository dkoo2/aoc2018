#include <string>
#include <vector>
#include <memory>

namespace aoc2018 {

class Polymer {
   public:
    explicit Polymer(std::string_view line);

    int Collapse() const;
    int ShortestAfterRemoval() const;

   private:
    std::vector<int> ascii_;
};

}  // namespace aoc2018
