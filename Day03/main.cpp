#include <iostream>
#include <fstream>
#include <vector>
#include "backpack.h"

int main() {

    std::vector<backpack> backpacks;
    int totalPriorities = 0;
    int totalBadgePriorities = 0;

    std::fstream input("Day03/input.txt");
    if (input.is_open()) {
        std::string line;
        while (std::getline(input, line)) {
            backpacks.push_back(backpack(line));
            totalPriorities += backpacks[backpacks.size() - 1].prioritiesSum;

            if (backpacks.size() % 3 == 0)
                totalBadgePriorities += backpacks[backpacks.size() - 1].commonItem(backpacks[backpacks.size() - 2], backpacks[backpacks.size() - 3]);
        }
    }
    std::cout << "The total priorities sum is " << totalPriorities << " and the total badge priorities is " << totalBadgePriorities;
}