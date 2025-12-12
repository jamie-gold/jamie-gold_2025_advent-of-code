#include <iostream>
#include <vector>

using bool_2D_vector_t = std::vector<std::vector<bool>>;

constexpr std::size_t MIN_ADJACENT_ROLLS = 4;

std::size_t removeAcessableRolls(bool_2D_vector_t& rolls);
bool isAccessable(const bool_2D_vector_t& rolls, int i, int j);

std::size_t removeAcessableRolls(bool_2D_vector_t& rolls) {
    std::size_t accessableCount = 0;
    std::vector<std::pair<int, int>> toRemove;

    for (int i = 0; i < rolls.size(); i++) {
        for (int j = 0; j < rolls[i].size(); j++) {
            if (rolls[i][j]) {
                std::size_t adjacencyCount = 0;

                if (isAccessable(rolls, i - 1, j - 1))  adjacencyCount++;
                if (isAccessable(rolls, i - 1, j))      adjacencyCount++;
                if (isAccessable(rolls, i - 1, j + 1))  adjacencyCount++;
                if (isAccessable(rolls, i, j - 1))      adjacencyCount++;
                if (isAccessable(rolls, i, j + 1))      adjacencyCount++;
                if (isAccessable(rolls, i + 1, j - 1))  adjacencyCount++;
                if (isAccessable(rolls, i + 1, j))      adjacencyCount++;
                if (isAccessable(rolls, i + 1, j + 1))  adjacencyCount++;

                if (adjacencyCount > MIN_ADJACENT_ROLLS) {
                    accessableCount++;
                    toRemove.emplace_back(i, j);
                }
            }
        }
    }

    for (auto& [i, j] : toRemove) {
        rolls[i][j] = false;
    }

    return accessableCount;
}

bool isAccessable(const bool_2D_vector_t& rolls, int i, int j) {
    if (!(i >= 0 && j >= 0 && i < rolls.size() && j < rolls[i].size())) return true;

    return !rolls[i][j];
}

int main() {
    bool_2D_vector_t rolls;
    
    bool firstInput = true;
    std::size_t rowSize;

    std::string currRow;
    std::size_t i = 0;
    while (std::cin >> currRow) {
        if (firstInput) {
            rowSize = currRow.size();
            firstInput = false;
        }

        rolls.emplace_back(rowSize, false);
        for (std::size_t j = 0; j < rowSize; j++) {
            if (currRow[j] == '@') rolls[i][j] = true;
        }

        i++;
    }

    
    std::size_t accessableRolls = 0;
    std::size_t currRolls = 0;
    do {
        currRolls = removeAcessableRolls(rolls);
        accessableRolls += currRolls;
    } while (currRolls > 0);

    std::cout << "Amount of accessable rolls: " << accessableRolls << '\n';

    return 0;
}