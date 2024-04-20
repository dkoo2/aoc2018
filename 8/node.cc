#include "node.h"

#include <cassert>
#include <iostream>
#include <span>
#include <string>

namespace aoc2018 {

Root::Root(std::span<const std::string> lines) {
    raw_.reserve(lines.size());
    for (const std::string& l : lines) {
        raw_.push_back(std::stoi(l));
    }
}

namespace {

// Returns pair of <sum, next_index>
std::pair<int, int> ProcessChild(const std::span<const int> raw,
                                 const int start) {
    if (start >= raw.size()) return std::make_pair(0, start);

    const int children = raw[start];
    const int metadata = raw[start + 1];
    int sum = 0;
    if (children == 0) {
        for (int i = 0; i < metadata; ++i) {
            sum += raw[2 + i + start];
        }
        return std::make_pair(sum, 2 + metadata + start);
    }
    std::pair<int, int> np = {-1, start + 2};
    for (int i = 0; i < children; ++i) {
        np = ProcessChild(raw, np.second);
        sum += np.first;
    }
    for (int i = 0; i < metadata; ++i) {
        sum += raw[np.second + i];
    }
    return std::make_pair(sum, np.second + metadata);
}

std::pair<int64_t, int> ProcessIndexedChild(const std::span<const int> raw,
                                            const int start) {
    if (start >= raw.size()) return std::make_pair(0, start);

    const int children = raw[start];
    const int metadata = raw[start + 1];

    if (children == 0) {
        int64_t sum = 0;
        for (int i = 0; i < metadata; ++i) {
            sum += raw[2 + i + start];
        }
        return std::make_pair(sum, 2 + metadata + start);
    }

    std::vector<int64_t> sums;
    sums.reserve(children);

    std::pair<int64_t, int> np = {-1, start + 2};
    for (int i = 0; i < children; ++i) {
        np = ProcessIndexedChild(raw, np.second);
        sums.push_back(np.first);
    }
    assert(sums.size() == children);

    int64_t md_sum = 0;
    for (int i = 0; i < metadata; ++i) {
        const int index = raw[np.second + i];
        if (index == 0 || index - 1 >= sums.size()) continue;
        md_sum += sums[index - 1];
    }
    return std::make_pair(md_sum, np.second + metadata);
}

}  // namespace

int Root::MetadataSum() const { return ProcessChild(raw_, 0).first; }

int64_t Root::IndexedSum() const { return ProcessIndexedChild(raw_, 0).first; }

}  // namespace aoc2018