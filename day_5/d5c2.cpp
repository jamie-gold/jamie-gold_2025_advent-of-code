#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <string>
#include <utility>
#include <set>
#include <vector>

using range_t = std::pair<std::uint64_t, std::uint64_t>;

std::size_t maxFreshIngrediantIds(const std::vector<range_t>& ingrediantRanges);
bool rangesOverlap(range_t range1, range_t range2);

std::ostream& operator<<(std::ostream& os, const range_t& range) {
    os << range.first << '-' << range.second;
    return os;
}

std::size_t maxFreshIngrediantIds(const std::vector<range_t>& ingrediantRanges) {
    std::vector<range_t> condensedRanges = ingrediantRanges;

    bool condensed = false;
    while (!condensed) {
        condensed = true;

        for (auto i = condensedRanges.begin(); i != condensedRanges.end(); i++) {
            for (auto j = i + 1; j != condensedRanges.end(); j++) {
                if (rangesOverlap(*i, *j)) {
                    condensed = false;
                    i->first = j->first < i->first ? j->first : i->first;
                    i->second = j->second > i->second ? j->second : i->second;

                    condensedRanges.erase(j);

                    break;
                }
            }

            if (!condensed) break;
        }
    }

    std::size_t freshIngrediantIdAmount = 0;
    for (auto& range : condensedRanges) {
        freshIngrediantIdAmount  += range.second - range.first + 1;
    }

    return freshIngrediantIdAmount;
}

bool rangesOverlap(range_t range1, range_t range2) {
    return range1.first <= range2.second && range2.first <= range1.second;
}

int main() {
    std::vector<range_t> ingrediantRanges;

    std::string outString;
    while (true) {
        std::getline(std::cin, outString);
        if (outString.empty()) break;

        std::size_t delimiterPos = outString.find('-'); 
        std::uint64_t start = std::stoul(outString.substr(0, delimiterPos));
        std::uint64_t end = std::stoul(outString.substr(delimiterPos + 1, outString.size() - delimiterPos - 1));

        ingrediantRanges.emplace_back(start, end);
    }

    std::size_t maxFreshAmount = maxFreshIngrediantIds(ingrediantRanges);
    std::cout << "Max amount of fresh ids: " << maxFreshAmount << '\n';
}