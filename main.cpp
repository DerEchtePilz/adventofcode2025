#include <print>

#include "main.h"

#include <chrono>

#include "src/day1.h"
#include "src/day2.h"
#include "src/day3.h"
#include "src/day4.h"
#include "src/day5.h"
#include "src/day6.h"
#include "src/day7.h"
#include "src/day8.h"

int main() {
    printDay(1, day1::runDay, day1::runDay);
    printDay(2, day2::runDay, day2::runDay);
    printDay(3, day3::runDay, day3::runDay);
    printDay(4, day4::runDay, day4::runDay);
    printDay(5, day5::runDay, day5::runDay);
    printDay(6, day6::runDay, day6::runDay);
    printDay(7, day7::runDay, day7::runDay);
    printDay(8, day8::runDay, day8::runDay);
}

void printDay(unsigned long long day, dayFunction one, dayFunction two) {
    std::vector<std::string> input = readFile("day" + std::to_string(day) + ".txt");

    auto start1 = std::chrono::system_clock::now();
    unsigned long long part1 = one(false, input);
    auto end1 = std::chrono::system_clock::now();
    auto start2 = std::chrono::system_clock::now();
    unsigned long long part2 = two(true, input);
    auto end2 = std::chrono::system_clock::now();

    double ms1 = std::chrono::duration<double, std::milli>(end1 - start1).count();
    double ms2 = std::chrono::duration<double, std::milli>(end2 - start2).count();

    std::println("Day {} solutions:\n  Part 1: {} ({:.2f} ms)\n  Part 2: {} ({:.2f} ms)", day, part1, ms1, part2, ms2);
}
