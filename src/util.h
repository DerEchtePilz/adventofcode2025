#pragma once
#include <fstream>
#include <ranges>
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

inline auto split(const std::string& str, char delim) -> std::vector<std::string> {
    auto toString = [](auto&& r) -> std::string {
        const char* data = &*r.begin();
        const auto size = static_cast<size_t>(std::ranges::distance(r));
        return std::string{data, size};
    };

    auto range = str |
                       std::ranges::views::split(delim) |
                       std::ranges::views::transform(toString);
    return {std::ranges::begin(range), std::ranges::end(range)};
}

inline std::string ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) {
        return !std::isspace(c);
    }));
    return s;
}

inline std::string rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char c) {
        return !std::isspace(c);
    }).base(), s.end());
    return s;
}

inline std::string trim(std::string& s) {
    ltrim(s);
    rtrim(s);
    return s;
}

template <typename T>
int digitsInNumber(T number) {
    return std::log10(number) + 1;
}
