#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::uint64_t> findInvalidIds(std::uint64_t start, std::uint64_t end) {
    std::vector<std::uint64_t> ids;

    for (std::uint64_t i = start; i <= end; i++) {
        std::string currId = std::to_string(i);

        if (currId.size() % 2 == 0) {
            std::string idHalf1 = currId.substr(0, currId.size() / 2);
            std::string idHalf2 = currId.substr(currId.size() / 2, currId.size() / 2);

            if (idHalf1 == idHalf2) ids.push_back(i);
        }
    }

    return ids;
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