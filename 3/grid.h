#pragma once

#include <span>
#include <string>

namespace aoc2018 {

struct Fill {
    int id;
    int left_offset;
    int top_offset;
    int width;
    int height;
};

class Grid {
   public:
    explicit Grid(std::span<const std::string> lines);

    int Overlaps() const;
    int Intact() const;

   private:
    std::vector<Fill> fills_;
};

}  // namespace aoc2018
