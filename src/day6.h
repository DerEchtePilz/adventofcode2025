#pragma once

#include "util.h"

namespace day6 {
    inline void buildNumbers(std::vector<std::string>& input, std::vector<std::vector<unsigned long long>>& output, bool partTwo) {
        if (!partTwo) {
            std::vector<std::vector<unsigned long long>> numbers;
            int iter = 0;
            for (std::string& line : input) {
                std::vector<std::string> unsanitized = split(trim(line), ' ');
                std::string& first = unsanitized[0];
                if (!(first[0] == '*' || first[0] == '+')) {
                    int index = 0;
                    for (std::string& s : unsanitized) {
                        if (s.empty()) {
                            continue;
                        }
                        if (iter == 0) {
                            std::vector<unsigned long long> number;
                            number.push_back(std::stoull(s));
                            output.push_back(number);
                        } else {
                            std::vector<unsigned long long>& number = output[index];
                            number.push_back(std::stoull(s));
                        }
                        index++;
                    }
                }
                iter++;
            }
        } else {
            bool canContinue = true;
            while (canContinue) {
                std::string& first = input[0];
                std::string& second = input[1];
                std::string& third = input[2];
                std::string& fourth = input[3];
                int commonWhitespace = 0;
                bool isCommonWhitespace = first[commonWhitespace] == ' ' && second[commonWhitespace] == ' ' && third[commonWhitespace] == ' ' && fourth[commonWhitespace] == ' ';
                while (!isCommonWhitespace && (commonWhitespace + 1) < first.size()) {
                    commonWhitespace++;
                    isCommonWhitespace = first[commonWhitespace] == ' ' && second[commonWhitespace] == ' ' && third[commonWhitespace] == ' ' && fourth[commonWhitespace] == ' ';
                }
                if (commonWhitespace + 1 >= first.size()) {
                    commonWhitespace++;
                }
                std::string firstPart = first.substr(0, commonWhitespace);
                std::string secondPart = second.substr(0, commonWhitespace);
                std::string thirdPart = third.substr(0, commonWhitespace);
                std::string fourthPart = fourth.substr(0, commonWhitespace);

                if ((commonWhitespace + 1 < first.size())) {
                    first = first.substr(commonWhitespace + 1);
                    second = second.substr(commonWhitespace + 1);
                    third = third.substr(commonWhitespace + 1);
                    fourth = fourth.substr(commonWhitespace + 1);
                } else {
                    canContinue = false;
                }

                std::vector<unsigned long long> current;
                for (int i = firstPart.size() - 1; i >= 0; i--) {
                    char cFirst = firstPart[i];
                    char cSecond = secondPart[i];
                    char cThird = thirdPart[i];
                    char cFourth = fourthPart[i];
                    unsigned long long number = 0;
                    if (cFirst != ' ') {
                        number = cFirst - '0';
                    }
                    if (cSecond != ' ') {
                        number = number * 10 + cSecond - '0';
                    }
                    if (cThird != ' ') {
                        number = number * 10 + cThird - '0';
                    }
                    if (cFourth != ' ') {
                        number = number * 10 + cFourth - '0';
                    }
                    current.push_back(number);
                }
                output.push_back(current);
            }
        }
    }

    inline unsigned long long runDay(bool partTwo, std::vector<std::string>& input) {
        std::vector<std::vector<unsigned long long>> numbers;
        std::vector<char> operators;
        std::ranges::copy_if(input[4], std::back_inserter(operators), [](unsigned char c) {
            return !std::isspace(c);
        });

        buildNumbers(input, numbers, partTwo);

        unsigned long long result = 0;
        for (size_t i = 0; i < operators.size(); i++) {
            const char op = operators[i];
            unsigned long long intermediate = op == '+' ? 0 : 1;
            std::vector<unsigned long long>& current = numbers[i];
            for (unsigned long long number : current) {
                if (op == '+') {
                    intermediate += number;
                } else {
                    intermediate *= number;
                }
            }
            result += intermediate;
        }
        return result;
    }
}
