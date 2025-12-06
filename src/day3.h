#pragma once

namespace day3 {
    inline unsigned long long getBiggestNumber(const std::string& bank, const int start, const int end) {
        unsigned long long biggest = 0;

        int biggestIndex = start;
        unsigned long long currentBiggest = bank[start] - '0';

        for (int i = biggestIndex + 1; i < bank.size() - end; i++) {
            if (bank[i] - '0' > currentBiggest) {
                currentBiggest = bank[i] - '0';
                biggestIndex = i;
            }
        }
        biggest = currentBiggest;
        biggestIndex++;

        if (end == 0) {
            return biggest;
        }
        const unsigned long long intermediateHigh = biggest * static_cast<unsigned long long>(std::pow(10, end));
        const unsigned long long intermediateLow = getBiggestNumber(bank, biggestIndex, end - 1);
        return intermediateHigh + intermediateLow;
    }

    inline unsigned long long runDay(bool partTwo, std::vector<std::string>& input) {
        unsigned long long result = 0;
        for (const std::string& bank : input) {
            unsigned long long biggest = 0;
            if (!partTwo) {
                biggest = getBiggestNumber(bank, 0, 1);
            } else {
                biggest = getBiggestNumber(bank, 0, 11);
            }
            result += biggest;
        }
        return result;
    }
}
