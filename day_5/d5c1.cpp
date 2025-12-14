#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

bool validIngrediant(const std::vector<std::pair<std::uint64_t, std::uint64_t>>& ingrediantRanges, std::uint64_t ingrediantId) {
    return std::any_of(ingrediantRanges.begin(), ingrediantRanges.end(), 
    [&ingrediantId](const std::pair<std::uint64_t, std::uint64_t>& range) {
        return ingrediantId >= range.first && ingrediantId <= range.second;
    });
}

int main() {
    std::vector<std::pair<std::uint64_t, std::uint64_t>> ingrediantRanges;
    std::size_t freshAmount = 0;

    std::string outString;
    while (true) {
        std::getline(std::cin, outString);
        if (outString.empty()) break;

        std::size_t delimiterPos = outString.find('-'); 
        std::uint64_t start = std::stoul(outString.substr(0, delimiterPos));
        std::uint64_t end = std::stoul(outString.substr(delimiterPos + 1, outString.size() - delimiterPos - 1));

        ingrediantRanges.emplace_back(start, end);
    }

    while (std::cin >> outString) {
        if (validIngrediant(ingrediantRanges, std::stoul(outString))) freshAmount++;
    }

    std::cout << "Amount of fresh ids: " << freshAmount << '\n';
}