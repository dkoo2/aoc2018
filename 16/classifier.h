#include <array>
#include <span>
#include <string>
#include <vector>

#include "opcode.h"

namespace aoc2018 {

struct P {
    std::array<int, 4> before;
    std::array<int, 4> after;
    int op_mask;
    int rA;
    int rB;
    int rC;
};

struct Instruction {
    int mask;
    int A;
    int B;
    int C;
};

class Classifier {
   public:
    Classifier(std::span<const std::vector<std::string>> inputs,
               std::span<const std::string> instructions);

    int Part1() const;

    int Part2() const;

   private:
    std::vector<P> inputs_;

    std::vector<Instruction> instructions_;
};

}  // namespace aoc2018
