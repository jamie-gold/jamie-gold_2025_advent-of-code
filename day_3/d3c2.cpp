#include <algorithm>
#include <array>
#include <cinttypes>
#include <cmath>
#include <iostream>
#include <string>

constexpr std::size_t BATTERY_AMOUNT = 12;

bool elementPredicate(char lhs, char rhs) {     // Prioritises left most element if equal
    return lhs < rhs || lhs == rhs;
}

std::uint64_t maximumJoltage(const std::string& bank) {
    std::array<std::string::const_reverse_iterator, BATTERY_AMOUNT + 1> values;

    for (std::size_t i = 0; i < BATTERY_AMOUNT; i++) {
        if (i == 0) {
            values[i] = std::max_element(bank.rbegin() + (BATTERY_AMOUNT - 1), bank.rend(), elementPredicate);
        } else {
            values[i] = std::max_element(bank.rbegin() + (BATTERY_AMOUNT - 1 - i), values[i - 1], elementPredicate);
        }
    }

    std::uint64_t retVal = 0;

    for (std::size_t i = 0; i < BATTERY_AMOUNT; i++) {
        retVal += (*values[i] - '0') * std::pow(10, BATTERY_AMOUNT - 1 - i);
    }

    return retVal;
}

int main() {
    std::uint64_t joltage = 0;
    std::string bank;
    
    while (std::cin >> bank) {
        joltage += maximumJoltage(bank);
    }

    std::cout << "Maximum joltage is: " << joltage << '\n';
}