#pragma once

#include <vector>
#include <map>

namespace aoc2018 {

struct TimeStamp {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    friend auto operator<=>(const TimeStamp&, const TimeStamp&) = default;
};


struct IntermediateRepr {
    TimeStamp t;
    std::string metadata;
};

struct SleepTimestamps {
    TimeStamp fall_asleep;
    TimeStamp wake_up;
};

struct Shift {
    int guard_id;
    TimeStamp start;
    std::vector<SleepTimestamps> sleep;
};

struct GuardProfile {
    int guard_id;
    int total_sleep;
    // Timestamp asleep minute.
    std::map<int, int> timestamp_asleep_counter;
};

}  // namespace aoc2018