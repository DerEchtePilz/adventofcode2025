#pragma once

#include <set>
#include <map>
#include <unordered_map>

template <>
struct std::hash<std::pair<int, int>> {
    size_t operator()(const std::pair<int, int>& p) const noexcept {
        return hash<int>()(p.first) ^ hash<int>()(p.second);
    }
};

namespace day7 {
    inline unsigned long long generateBeams(std::vector<std::string>& input, int iteration, std::set<int>& beams, int pastBeams) {
        if (iteration == 0) {
            return pastBeams;
        }
        std::set<int> currentBeams;
        int hitSplitters = 0;
        std::string& line = input[input.size() - iteration];
        for (int i = 0; i < line.size(); i++) {
            if (std::ranges::find(beams, i) != beams.end() && line[i] == '^') {
                if (std::ranges::find(beams, i - 1) == beams.end()) {
                    currentBeams.insert(i - 1);
                }
                if (std::ranges::find(beams, i + 1) == beams.end()) {
                    currentBeams.insert(i + 1);
                }
                beams.erase(i);
                hitSplitters++;
            }
        }
        for (int i : beams) {
            currentBeams.insert(i);
        }
        return generateBeams(input, iteration - 1, currentBeams, pastBeams + hitSplitters);
    }

    inline int findStart(std::vector<std::string>& input) {
        int start = -1;
        for (int i = 0; i < input[0].size(); i++) {
            if (input[0][i] == 'S') {
                start = i;
                break;
            }
        }
        return start;
    }

    inline unsigned long long generateBeams(std::vector<std::string>& input, int iteration) {
        std::set currentBeams = {findStart(input)};
        return generateBeams(input, iteration - 1, currentBeams, 0);
    }

    inline unsigned long long countTimeLines(std::vector<std::string>& input, int iteration, int currentBeam, std::unordered_map<std::pair<int, int>, unsigned long long>& timeLineMemo) {
        if (iteration == 0) {
            return 1;
        }
        std::pair<int, int> key = std::make_pair(iteration, currentBeam);
        if (timeLineMemo.contains(key)) {
            return timeLineMemo[{iteration, currentBeam}];
        }
        std::string& line = input[input.size() - iteration];
        if (std::ranges::find(line, '^') == line.end()) {
            return countTimeLines(input, iteration - 1, currentBeam, timeLineMemo);
        }
        unsigned long long timelines = 0;
        if (line[currentBeam] == '^') {
            timelines += countTimeLines(input, iteration - 1, currentBeam - 1, timeLineMemo);
            timelines += countTimeLines(input, iteration - 1, currentBeam + 1, timeLineMemo);
        } else {
            return countTimeLines(input, iteration - 1, currentBeam, timeLineMemo);
        }
        timeLineMemo[{iteration, currentBeam}] = timelines;
        return timelines;
    }

    inline unsigned long long countTimeLines(std::vector<std::string>& input, int iteration) {
        std::unordered_map<std::pair<int, int>, unsigned long long> timelines;
        return countTimeLines(input, iteration - 1, findStart(input), timelines);
    }

    inline unsigned long long runDay(bool partTwo, std::vector<std::string>& input) {
        return !partTwo
                   ? generateBeams(input, input.size())
                   : countTimeLines(input, input.size());
    }
}
