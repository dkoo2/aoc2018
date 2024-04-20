#include <span>
#include <string>
#include <vector>

namespace aoc2018 {

class Root {
   public:
    explicit Root(std::span<const std::string> lines);

    int MetadataSum() const;

    int64_t IndexedSum() const;

   private:
    std::vector<int> raw_;
};

}  // namespace aoc2018
