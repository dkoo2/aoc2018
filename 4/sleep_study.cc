#include "sleep_study.h"

#include <cassert>
#include <iostream>
#include <regex>
#include <span>
#include <string>

#include "types.h"

namespace aoc2018 {

SleepStudy::SleepStudy(std::span<const std::string> lines) {
    std::regex date("\\[([0-9]+)-([0-9]+)-([0-9]+) ([0-9]+):([0-9]+)\\] (.*)");
    std::vector<IntermediateRepr> irs;
    irs.reserve(lines.size());
    for (const std::string& l : lines) {
        std::smatch match;
        if (std::regex_search(l.begin(), l.end(), match, date)) {
            TimeStamp t;
            t.year = std::stoi(match[1]);
            t.month = std::stoi(match[2]);
            t.day = std::stoi(match[3]);
            t.hour = std::stoi(match[4]);
            t.minute = std::stoi(match[5]);
            irs.push_back(IntermediateRepr{.t = t, .metadata = match[6]});
        } else {
            assert(false);
        }
    }
    std::sort(irs.begin(), irs.end(),
              [](const IntermediateRepr& lhs, const IntermediateRepr& rhs) {
                  return lhs.t < rhs.t;
              });
    std::regex shift_start_match("Guard #([0-9]+) begins shift");
    for (const IntermediateRepr& ir : irs) {
        std::smatch match;
        if (ir.metadata == "wakes up") {
            assert(!shifts_.empty());
            Shift& shift = shifts_.back();
            assert(!shift.sleep.empty());
            SleepTimestamps& sleep_record = shift.sleep.back();
            sleep_record.wake_up = ir.t;
        } else if (ir.metadata == "falls asleep") {
            assert(!shifts_.empty());
            Shift& shift = shifts_.back();
            SleepTimestamps start_sleep;
            start_sleep.fall_asleep = ir.t;
            shift.sleep.push_back(std::move(start_sleep));
        } else if (std::regex_search(ir.metadata.begin(), ir.metadata.end(),
                                     match, shift_start_match)) {
            const int guard_id = std::stoi(match[1]);
            Shift shift;
            shift.guard_id = guard_id;
            shift.start = ir.t;
            shifts_.push_back(std::move(shift));
        }
    }
}

std::pair<int, int> SleepStudy::Strategy() const {
    std::map<int, GuardProfile> guards;
    for (const Shift& shift : shifts_) {
        const int id = shift.guard_id;
        auto it = guards.find(id);
        if (it == guards.end()) {
            GuardProfile gp;
            gp.guard_id = id;
            guards[id] = gp;
        }
        GuardProfile& shift_gp = guards[id];
        for (const SleepTimestamps& st : shift.sleep) {
            const int start_min = st.fall_asleep.minute;
            const int end_min = st.wake_up.minute;
            for (int i = start_min; i <= end_min; ++i) {
                ++shift_gp.total_sleep;
                ++shift_gp.timestamp_asleep_counter[i];
            }
        }
    }
    // Find most sleeping guard.
    int most_sleep_id = -1;
    int max_sleep = -1;
    for (const auto& [guard_id, pp] : guards) {
        if (pp.total_sleep > max_sleep) {
            max_sleep = pp.total_sleep;
            most_sleep_id = guard_id;
        }
    }
    assert(max_sleep > 0 && guards.contains(most_sleep_id));
    const GuardProfile& most_sleep_profile = guards[most_sleep_id];

    int best_min = -1;
    int best_count = -1;
    for (const auto& [min, count] :
         most_sleep_profile.timestamp_asleep_counter) {
        if (count > best_count) {
            best_count = count;
            best_min = min;
        }
    }
    const int strategy_one = best_min * most_sleep_id;

    // Run strategy 2.
    int most_asleep_count = -1;
    int most_asleep_min = -1;
    int msc_id = -1;
    for (const auto& [guard_id, pp] : guards) {
        for (const auto& [minute, count] : pp.timestamp_asleep_counter) {
            if (count > most_asleep_count) {
                most_asleep_count = count;
                msc_id = guard_id;
                most_asleep_min = minute;
            }
        }
    }
    const int strategy_two = most_asleep_min * msc_id;

    return std::make_pair(strategy_one, strategy_two);
}

}  // namespace aoc2018