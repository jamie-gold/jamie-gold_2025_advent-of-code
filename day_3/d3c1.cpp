#include <algorithm>
#include <iostream>
#include <string>

int maximumJoltage(const std::string& bank) {
    auto firstVal = std::max_element(bank.rbegin() + 1, bank.rend(), 
        [](auto& lhs, auto& rhs) { return lhs < rhs || lhs == rhs; });  // Prioritises left most element if equal
    auto secondVal = std::max_element(bank.rbegin(), firstVal);

    return (*firstVal - '0') * 10 + (*secondVal - '0');
}

int main() {
    unsigned int joltage = 0;
    std::string bank;
    
    while (std::cin >> bank) {
        joltage += maximumJoltage(bank);
    }

    std::cout << "Maximum joltage is: " << joltage << '\n';
}