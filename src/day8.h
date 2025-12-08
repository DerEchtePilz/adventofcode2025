#pragma once

#include "util.h"

#include <functional>

struct Connection {
    Vector3 point;

    double distance = -1;
    Vector3* shortestDistance = nullptr;

    bool operator==(const Connection& rhs) const {
        return point == rhs.point && shortestDistance == rhs.shortestDistance || point == *rhs.shortestDistance && *shortestDistance == rhs.point;
    }

    bool operator<(const Connection& rhs) const {
        return distance < rhs.distance;
    }
};

template <>
struct std::hash<Vector3> {
    std::size_t operator()(const Vector3& x) const noexcept {
        size_t hx = std::hash<int>()(x.x);
        size_t hy = std::hash<int>()(x.y);
        size_t hz = std::hash<int>()(x.z);

        size_t seed = 0;
        seed ^= hx + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hy + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hz + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

template <>
struct std::hash<std::pair<std::shared_ptr<Vector3>, std::shared_ptr<Vector3>>> {
    size_t operator()(const std::pair<std::shared_ptr<Vector3>, std::shared_ptr<Vector3>>& x) const noexcept{
        size_t h1 = hash<Vector3>()(*(x.first));
        size_t h2 = hash<Vector3>()(*(x.second));

        size_t seed = 0;
        seed ^= h1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

namespace day8 {
    inline unsigned long long runDay(bool partTwo, std::vector<std::string>& input) {
        std::vector<Vector3> positions;
        positions.reserve(input.size());
        for (std::string& line : input) {
            int number = 0;
            int index = 0;
            char currentPos = 'x';
            Vector3 vector;
            while (index < line.size()) {
                if (line[index] == ',') {
                    switch (currentPos) {
                        case 'x':
                            vector.x = number;
                            currentPos = 'y';
                            break;
                        case 'y':
                            vector.y = number;
                            currentPos = 'z';
                    }
                    number = 0;
                    index++;
                    continue;
                }
                number = number * 10 + (line[index] - '0');
                index++;
            }
            vector.z = number;
            positions.push_back(vector);
        }

        std::map<double, Connection> allConnections;
        std::vector<std::set<Vector3>> connections;
        std::unordered_map<Vector3, int> indices;

        for (Vector3& vector : positions) {
            connections.push_back({vector});
            indices[vector] = connections.size() - 1;
        }

        for (int i = 0; i < positions.size(); i++) {
            Vector3& firstP = positions[i];
            for (Vector3& secondP : positions) {
                Vector3& first = firstP;
                Vector3& second = secondP;
                if (first == second) {
                    continue;
                }
                double distance = std::sqrt(std::pow(second.x - first.x, 2) + std::pow(second.y - first.y, 2) + std::pow(second.z - first.z, 2));
                if (allConnections.contains(distance)) {
                    continue;
                }
                allConnections[distance] = {first, distance, &second};
            }
        }

        std::vector<double> keys;
        for (auto it = allConnections.begin(); it != allConnections.end(); it++) {
            keys.push_back(it->first);
        }
        std::ranges::sort(keys, [](const double& lhs, const double& rhs) {
            return lhs < rhs;
        });

        bool willConnect = false;
        int iterations = 0;
        bool condition = true;
        Connection connectingConnection;

        while (condition) {
            Connection currentShortest = allConnections[keys[iterations]];
            iterations++;
            condition = !partTwo ? iterations < 1000 : !willConnect;
            Vector3 first = currentShortest.point;
            Vector3 second = *currentShortest.shortestDistance;

            int firstIndex = -1;
            int secondIndex = -1;

            for (int i = 0; i < connections.size(); i++) {
                if (firstIndex == -1 && std::ranges::find(connections[i], first) != connections[i].end()) {
                    firstIndex = i;
                }
                if (secondIndex == -1 && std::ranges::find(connections[i], second) != connections[i].end()) {
                    secondIndex = i;
                }
                if (firstIndex != -1 && secondIndex != -1) {
                    break;
                }
            }

            if (firstIndex == secondIndex) {
                continue;
            }

            if (connections.size() == 2 && firstIndex != secondIndex) {
                connectingConnection = currentShortest;
                willConnect = true;
                continue;
            }

            std::set<Vector3>& firstSet = connections[firstIndex];
            std::set<Vector3>& secondSet = connections[secondIndex];

            firstSet.insert(secondSet.begin(), secondSet.end());
            connections.erase(connections.begin() + secondIndex);

            for (const Vector3& vector : firstSet) {
                indices[vector] = firstIndex;
            }
            for (int i = secondIndex; i < connections.size(); i++) {
                for (const Vector3& vector : connections[i]) {
                    indices[vector] = i;
                }
            }
        }

        std::ranges::sort(connections, [](const std::set<Vector3>& a, const std::set<Vector3>& b) {
            return a.size() > b.size();
        });

        if (!partTwo) {
            unsigned long long result = 1;
            for (int i = 0; i < 3; i++) {
                result *= connections[i].size();
            }
            return result;
        }
        return connectingConnection.point.x * connectingConnection.shortestDistance->x;
    }
}
