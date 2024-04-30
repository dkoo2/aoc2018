
#include "classifier.h"

#include <cassert>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <span>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace aoc2018 {

namespace {

std::array<int, 4> ParseState(const std::string& str,
                              const std::regex& regexp) {
    std::smatch matcher;
    const bool matched =
        std::regex_search(str.begin(), str.end(), matcher, regexp);
    if (!matched) {
        std::exit(-1);
    }
    assert(matched);
    const std::string r0 = matcher[1];
    const std::string r1 = matcher[2];
    const std::string r2 = matcher[3];
    const std::string r3 = matcher[4];
    return {std::stoi(r0), std::stoi(r1), std::stoi(r2), std::stoi(r3)};
}

}  // namespace

Classifier::Classifier(std::span<const std::vector<std::string>> inputs,
                       std::span<const std::string> instructions) {
    const std::regex register_regexp("([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+)");
    const std::regex register_beforeregex(
        "Before.*\\[([0-9]+), ([0-9]+), ([0-9]+), ([0-9]+)\\].*");
    const std::regex register_aftergregex(
        "After.*\\[([0-9]+), ([0-9]+), ([0-9]+), ([0-9]+)\\].*");
    for (const std::vector<std::string>& in : inputs) {
        if (in.size() != 3) continue;
        const std::string& before = in[0];
        const std::string& registers = in[1];
        const std::string& after = in[2];

        std::array<int, 4> parsed_before =
            ParseState(before, register_beforeregex);
        std::array<int, 4> parsed_after =
            ParseState(after, register_aftergregex);
        std::smatch r_matcher;
        const bool r_match = std::regex_search(
            registers.begin(), registers.end(), r_matcher, register_regexp);
        if (!r_match) std::exit(-1);
        inputs_.push_back({.before = parsed_before,
                           .after = parsed_after,
                           .op_mask = std::stoi(r_matcher[1]),
                           .rA = std::stoi(r_matcher[2]),
                           .rB = std::stoi(r_matcher[3]),
                           .rC = std::stoi(r_matcher[4])});
    }

    for (const std::string& ist : instructions) {
        if (ist.empty()) continue;
        std::smatch i_matcher;
        const bool i_match = std::regex_search(ist.begin(), ist.end(),
                                               i_matcher, register_regexp);
        if (!i_match) std::exit(-1);
        instructions_.push_back({.mask = std::stoi(i_matcher[1]),
                                 .A = std::stoi(i_matcher[2]),
                                 .B = std::stoi(i_matcher[3]),
                                 .C = std::stoi(i_matcher[4])});
    }
}

int Classifier::Part1() const {
    int more_than_three = 0;
    for (const P& p : inputs_) {
        int counter = 0;
        for (int i = 0; i < 16; ++i) {
            const OpType optype = static_cast<OpType>(i);
            if (!Process(p.before, p.after, {optype, p.rA, p.rB, p.rC})) {
                continue;
            }
            if (counter++ >= 3) {
                ++more_than_three;
                break;
            }
        }
    }
    return more_than_three;
}

int Classifier::Part2() const {
    std::map<int, std::set<std::vector<OpType>>> mask_to_types;
    for (const P& p : inputs_) {
        const int mask = p.op_mask;
        std::vector<OpType> from_curr;
        for (int i = 0; i < 16; ++i) {
            const OpType optype = static_cast<OpType>(i);
            if (!Process(p.before, p.after, {optype, p.rA, p.rB, p.rC})) {
                continue;
            }
            from_curr.push_back(optype);
        }
        mask_to_types[mask].insert(std::move(from_curr));
    }

    std::unordered_map<int, OpType> matched;
    std::unordered_set<OpType> found_ops;
    do {
        for (const auto& [mask, types] : mask_to_types) {
            if (matched.contains(mask)) {
                continue;
            }
            for (const std::vector<OpType>& ops : types) {
                if (ops.size() == 1) {
                    matched[mask] = ops[0];
                    found_ops.insert(ops[0]);
                    break;
                }
                // See if we can eliminate already found ones to get an obvious
                // answer.
                int unknown_counter = 0;
                OpType suspect;
                for (const OpType ot : ops) {
                    if (!found_ops.contains(ot)) {
                        ++unknown_counter;
                        suspect = ot;
                        continue;
                    }
                }
                if (unknown_counter == 1) {
                    matched[mask] = suspect;
                    found_ops.insert(suspect);
                    break;
                }
            }
        }
    } while (matched.size() != 16);

    std::array<int, 4> registers = {0, 0, 0, 0};
    for (const Instruction ist : instructions_) {
        Do(registers, {.opcode = matched[ist.mask],
                       .rA = ist.A,
                       .rB = ist.B,
                       .rC = ist.C});
    }
    return registers[0];
}

}  // namespace aoc2018