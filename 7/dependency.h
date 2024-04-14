#include <span>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace aoc2018 {

class Graph {
   public:
    explicit Graph(std::span<const std::string> lines);

    std::vector<int> FindOrder() const;

    int TimeConsumed(std::span<const int> order);

   private:
    std::unordered_map<int, std::unordered_set<int>> prereqs_;
    std::unordered_set<int> all_;
};

}  // namespace aoc2018