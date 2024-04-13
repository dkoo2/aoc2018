#pragma once

#include <span>
#include <string>
#include <vector>
#include <utility>

#include "types.h"

namespace aoc2018 {


class SleepStudy {
   public:
    explicit SleepStudy(std::span<const std::string> lines);

    std::pair<int, int> Strategy() const;

   private:
    std::vector<Shift> shifts_;
};

}  // namespace aoc2018