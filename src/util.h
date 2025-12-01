#pragma once
#include <fstream>
#include <string>
#include <vector>

inline std::vector<std::string> readFile(const std::string& fileName) {
    std::string file;
    std::vector<std::string> lines;
    std::ifstream input("../days/" + fileName);
    while (std::getline(input, file)) {
        lines.push_back(file);
    }
    return lines;
}
