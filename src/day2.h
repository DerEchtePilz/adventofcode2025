#pragma once

#include <sstream>

#include "util.h"

namespace day2 {
    class Range {
        const unsigned long long lower;
        const unsigned long long upper;

        [[nodiscard]] static bool isPattern(unsigned long long number, int patternLength) {
            int digits = digitsInNumber(number);
            if (digits % patternLength != 0) {
                return false;
            }
            if (digits == patternLength) {
                return false;
            }
            unsigned long long firstPatternLengthDigits = number / static_cast<int>(std::pow(10, digits - patternLength));
            unsigned long long checkForPattern = firstPatternLengthDigits;
            int checkForPatternDigits = patternLength;
            while (checkForPatternDigits < digits) {
                checkForPattern *= static_cast<int>(std::pow(10, patternLength));
                checkForPattern += firstPatternLengthDigits;
                checkForPatternDigits += patternLength;
            }
            return checkForPattern == number;
        }

    public:
        Range(const unsigned long long lower, const unsigned long long upper) : lower(lower), upper(upper) {}

        [[nodiscard]] unsigned long long getInvalidIdsSum(bool partTwo) const {
            unsigned long long sum = 0;
            for (unsigned long long i = lower; i <= upper; i++) {
                int digits = digitsInNumber(i);
                if (!partTwo) {
                    if (digits % 2 != 0) {
                        continue;
                    }
                    const unsigned long long first = i / static_cast<int>(std::pow(10, digits / 2));
                    const unsigned long long second = i % static_cast<int>(std::pow(10, digits / 2));
                    if (first != second) {
                        continue;
                    }
                    sum += i;
                } else {
                    for (int j = 1; j <= digits; j++) {
                        if (isPattern(i, j)) {
                            sum += i;
                            break;
                        }
                    }
                }
            }
            return sum;
        }
    };

    inline unsigned long long runDay(bool partTwo, std::vector<std::string>& input) {
        std::vector<std::string> ranges = split(input[0], ',');
        unsigned long long invalidIdsSum = 0;
        for (const auto& rawRange : ranges) {
            std::vector<std::string> rangeParts = split(rawRange, '-');
            Range range(std::stoull(rangeParts[0]), std::stoull(rangeParts[1]));
            invalidIdsSum += range.getInvalidIdsSum(partTwo);
        }
        return invalidIdsSum;
    }
}
