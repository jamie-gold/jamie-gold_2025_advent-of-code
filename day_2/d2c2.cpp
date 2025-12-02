#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::uint64_t> findInvalidIds(std::uint64_t start, std::uint64_t end) {
    std::vector<std::uint64_t> invalidIds;

    for (std::uint64_t i = start; i <= end; i++) {
        std::string currId = std::to_string(i);

        for (size_t j = 1; j <= currId.size() / 2; j++) {
            if (currId.size() % j != 0) continue;

            std::vector<std::string> subIds;

            for (size_t k = 0; k < currId.size() / j; k++) {
                subIds.push_back(currId.substr(k * j, j));
            }

            if (subIds.size() != 0 && std::all_of(subIds.begin(), subIds.end(), [&](const std::string& id) { return id == subIds[0]; })) {
                invalidIds.push_back(i);
                break;
            }
        }
    }

    return invalidIds;
}

int main() {
    std::uint64_t invalidIdSum = 0;
    std::string currIdRange;

    while (std::getline(std::cin, currIdRange, ',')) {
        if (currIdRange == "") break;

        std::size_t delimiterPos = currIdRange.find('-'); 
        std::uint64_t start = std::stoul(currIdRange.substr(0, delimiterPos));
        std::uint64_t end = std::stoul(currIdRange.substr(delimiterPos + 1, currIdRange.size() - delimiterPos - 1));

        auto ids = findInvalidIds(start, end);
        std::for_each(ids.begin(), ids.end(), [&invalidIdSum] (std::uint64_t id) { invalidIdSum += id; });

        currIdRange.clear();
    }

    std::cout << "Sum of invalid ids is " << invalidIdSum << '\n';
}