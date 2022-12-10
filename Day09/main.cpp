#include <iostream>
#include <fstream>
#include <ios>
#include "rope.h"
#include <vector>

int main() {
    std::fstream input("Day09/input.txt");

    rope r(10);
    std::vector<Position> positions;

    if (input.is_open()) {
        std::string line;

        while (std::getline(input, line)) {
            char direction = line[0];
            std::string steps;

            for (int i = 2; i < line.size(); i++)
                steps += line[i];

            r.moveHead(direction, std::stoi(steps));
        }
    } else return 1;

    std::cout << "Tail has been in " << r.tailPositions.size() << " unique positions.";

    return 0;
}

