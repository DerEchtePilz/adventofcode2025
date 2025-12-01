#include "util.h"
#include "day1.h"
#include <print>

namespace day1 {
    int runDay(bool partTwo) {
        int pointsAtZero = 0;
        int start = 50;
        for (std::string& opWithNumber : readFile("day1.txt")) {
            char op = opWithNumber[0];
            int number = std::stoi(opWithNumber.substr(1, opWithNumber.size() - 1));
            if (op == 'L') {
                bool wasAtZeroInitially = start == 0;
                while (number > start) {
                    number = number - start;
                    start = 100;
                    if (partTwo && !wasAtZeroInitially) {
                        pointsAtZero += 1;
                    }
                    wasAtZeroInitially = false;
                }
                start = start - number;
                if (start == 0) {
                    pointsAtZero += 1;
                }
            } else {
                while ((start + number) > 100) {
                    number = number - 100;
                    if (partTwo) {
                        pointsAtZero += 1;
                    }
                }
                start = start + number;
                start %= 100;
                if (start == 0) {
                    pointsAtZero += 1;
                }
            }
        }
        return pointsAtZero;
    }
}
