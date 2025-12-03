#include <print>

#include "main.h"
#include "src/day1.h"
#include "src/day2.h"
#include "src/day3.h"

int main() {
    printDay(1, day1::runDay(false), day1::runDay(true));
    printDay(2, day2::runDay(false), day2::runDay(true));
    printDay(3, day3::runDay(false), day3::runDay(true));
}

void printDay(unsigned long long day, unsigned long long part1, unsigned long long part2) {
    std::println("Day {} solutions:\n  Part 1: {}\n  Part 2: {}", day, part1, part2);
}
