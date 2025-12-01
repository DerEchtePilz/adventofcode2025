#include <print>

#include "main.h"
#include "src/day1.h"

int main() {
    printDay(1, day1::runDay(false), day1::runDay(true));
}

void printDay(int day, int part1, int part2) {
    std::print("Day {} solutions:\n  Part 1: {}\n  Part 2: {}", day, part1, part2);
}
