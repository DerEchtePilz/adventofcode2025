#pragma once

typedef unsigned long long (* dayFunction)(bool partTwo);

void printDay(unsigned long long day, dayFunction one, dayFunction two);