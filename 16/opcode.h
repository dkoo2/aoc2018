#pragma once

#include <array>

namespace aoc2018 {

enum class OpType {
    kAddr = 0,
    kAddi = 1,
    kMulr = 2,
    kMuli = 3,
    kBanr = 4,
    kBani = 5,
    kBorr = 6,
    kBori = 7,
    kSetr = 8,
    kSeti = 9,
    kGtir = 10,
    kGtri = 11,
    kGtrr = 12,
    kEqir = 13,
    kEqri = 14,
    kEqrr = 15,
};

struct Input {
    OpType opcode;
    int rA;
    int rB;
    int rC;
};

bool Process(const std::array<int, 4>& before_registers,
             const std::array<int, 4>& after_registers, const Input& in);

void Do(std::array<int, 4>& res, const Input& in);

}  // namespace aoc2018