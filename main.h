#pragma once

#include <vector>

typedef unsigned long long (* dayFunction)(bool partTwo, std::vector<std::string>& input);

void printDay(unsigned long long day, dayFunction one, dayFunction two);