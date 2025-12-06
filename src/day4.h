#pragma once

namespace day4 {

    inline bool isAccessible(const std::vector<std::vector<char>>& grid, const int x, const int y) {
        int adjacent = 0;
        if (x - 1 >= 0 && grid[x - 1][y] == '@') {
            adjacent += 1;
        }
        if (x + 1 < grid.size() && grid[x + 1][y] == '@') {
            adjacent += 1;
        }
        if (y - 1 >= 0 && grid[x][y - 1] == '@') {
            adjacent += 1;
        }
        if (y + 1 < grid[x].size() && grid[x][y + 1] == '@') {
            adjacent += 1;
        }
        if (x - 1 >= 0 && y - 1 >= 0 && grid[x - 1][y - 1] == '@') {
            adjacent += 1;
        }
        if (x - 1 >= 0 && y + 1 < grid[x].size() && grid[x - 1][y + 1] == '@') {
            adjacent += 1;
        }
        if (x + 1 < grid.size() && y - 1 >= 0 && grid[x + 1][y - 1] == '@') {
            adjacent += 1;
        }
        if (x + 1 < grid.size() && y + 1 < grid[x].size() && grid[x + 1][y + 1] == '@') {
            adjacent += 1;
        }
        return adjacent < 4;
    }

    inline unsigned long long runDay(bool partTwo, std::vector<std::string>& input) {
        std::vector<std::vector<char>> grid;
        for (std::string& row : input) {
            std::vector<char> gridRow;
            for (char& c : row) {
                gridRow.push_back(c);
            }
            grid.push_back(gridRow);
        }
        unsigned long long accessible = 0;
        std::vector<std::vector<int>> toRemove;
        do {
            toRemove.clear();
            for (int x = 0; x < grid.size(); x++) {
                for (int y = 0; y < grid[x].size(); y++) {
                    if (grid[x][y] != '@') {
                        continue;
                    }
                    bool paperRollAccessible = isAccessible(grid, x, y);
                    accessible = (paperRollAccessible) ? accessible + 1 : accessible;
                    if (partTwo && paperRollAccessible) {
                        toRemove.push_back({x, y});
                    }
                }
            }
            for (std::vector<int>& row : toRemove) {
                grid[row[0]][row[1]] = '.';
            }
        } while (partTwo && !toRemove.empty());
        return accessible;
    }
}
