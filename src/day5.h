#pragma once

#include <algorithm>
#include <set>
#include "util.h"

namespace day5 {
    class Range {
        unsigned long long begin;
        unsigned long long end;
    public:
        Range(const unsigned long long begin, const unsigned long long end) : begin(begin), end(end) {}

        [[nodiscard]] bool isInRange(const unsigned long long number) const {
            return number >= begin && number <= end;
        }

        [[nodiscard]] unsigned long long countNumsInRange() const {
            return end - begin + 1;
        }

        [[nodiscard]] unsigned long long lower() const {
            return begin;
        }

        [[nodiscard]] unsigned long long upper() const {
            return end;
        }

        void moveEnd(const Range &other) {
            end = std::max(end, other.end);
        }

        bool operator<(const Range &other) const {
            return lower() < other.lower();
        }
    };

    inline unsigned long long runDay(bool partTwo) {
        std::vector<std::string> input = readFile("day5.txt");
        std::vector<Range> ranges;
        std::vector<unsigned long long> ids;
        bool rangesEnd = false;
        for (const std::string& line : input) {
            if (line.empty()) {
                rangesEnd = true;
                continue;
            }
            if (!rangesEnd) {
                std::vector<std::string> rangeParts = split(line, '-');
                ranges.emplace_back(std::stoull(rangeParts[0]), std::stoull(rangeParts[1]));
                continue;
            }
            ids.push_back(std::stoull(line));
        }

        std::sort(ranges.begin(), ranges.end());

        unsigned long long total = 0;
        std::set<unsigned long long> freshIds;
        std::vector<Range> mergedRanges;
        for (Range& range : ranges) {
            if (!partTwo) {
                for (unsigned long long& id : ids) {
                    if (range.isInRange(id)) {
                        freshIds.insert(id);
                    }
                }
            } else {
                if (mergedRanges.empty()) {
                    mergedRanges.emplace_back(range);
                    continue;
                }
                if (mergedRanges.back().isInRange(range.lower())) {
                    mergedRanges.back().moveEnd(range);
                    continue;
                }
                mergedRanges.emplace_back(range);
            }
        }

        if (!partTwo) {
            total = freshIds.size();
        } else {
            for (Range& range : mergedRanges) {
                total += range.countNumsInRange();
            }
        }
        return total;
    }
}
