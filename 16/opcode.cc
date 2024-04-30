#include "opcode.h"

#include <array>

namespace aoc2018 {

bool Process(const std::array<int, 4>& before_registers,
             const std::array<int, 4>& after_registers, const Input& in) {
    std::array<int, 4> res = before_registers;
    Do(res, in);
    return res == after_registers;
}

void Do(std::array<int, 4>& res, const Input& in) {
    switch (in.opcode) {
        case OpType::kAddr:
            res[in.rC] = res[in.rA] + res[in.rB];
            break;
        case OpType::kAddi:
            res[in.rC] = res[in.rA] + in.rB;
            break;
        case OpType::kMulr:
            res[in.rC] = res[in.rA] * res[in.rB];
            break;
        case OpType::kMuli:
            res[in.rC] = res[in.rA] * in.rB;
            break;
        case OpType::kBanr:
            res[in.rC] = res[in.rA] & res[in.rB];
            break;
        case OpType::kBani:
            res[in.rC] = res[in.rA] & in.rB;
            break;
        case OpType::kBorr:
            res[in.rC] = res[in.rA] | res[in.rB];
            break;
        case OpType::kBori:
            res[in.rC] = res[in.rA] | in.rB;
            break;
        case OpType::kSetr:
            res[in.rC] = res[in.rA];
            break;
        case OpType::kSeti:
            res[in.rC] = in.rA;
            break;
        case OpType::kGtir:
            res[in.rC] = in.rA > res[in.rB] ? 1 : 0;
            break;
        case OpType::kGtri:
            res[in.rC] = res[in.rA] > in.rB ? 1 : 0;
            break;
        case OpType::kGtrr:
            res[in.rC] = res[in.rA] > res[in.rB] ? 1 : 0;
            break;
        case OpType::kEqir:
            res[in.rC] = in.rA == res[in.rB] ? 1 : 0;
            break;
        case OpType::kEqri:
            res[in.rC] = res[in.rA] == in.rB ? 1 : 0;
            break;
        case OpType::kEqrr:
            res[in.rC] = res[in.rA] == res[in.rB] ? 1 : 0;
            break;
    }
}

}  // namespace aoc2018