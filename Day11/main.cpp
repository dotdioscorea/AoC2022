#include <iostream>
#include <fstream>
#include <vector>
#include "Monkey.h"

/* CHANGE PART 1 OR PART 2 IN Monkey.cpp and main.cpp USING #DEFINE part1/2 */

#define part1
//#define part2

void readMonkies (std::vector<Monkey> &monkies);

int main() {
    //READ AND PARSE INPUT FILE
    std::vector<Monkey> monkies;
    readMonkies(monkies);

    //PERFORM 1000 ROUNDS
#ifdef part1
    for (int round = 0; round < 20; round++)
        for (int m = 0; m < monkies.size(); m++)
            monkies[m].cycleMonkey(monkies);
#endif
#ifdef part2
    for (int round = 0; round < 10000; round++)
        for (int m = 0; m < monkies.size(); m++)
            monkies[m].cycleMonkey(monkies);
#endif

    //FIND LARGEST TWO VALUES OF MONKEY TIMES INSPECTED
    uint64_t c1 = 0, c2 = 0;
    for (Monkey monkey: monkies)
        if (monkey.timesInspected >= c1) { c2 = c1; c1 = monkey.timesInspected; }
        else if (monkey.timesInspected >= c2) { c2 = monkey.timesInspected; }

    //ANSWER TO PROBLEM
    std::cout << "Monkey business is " << std::to_string(c1 * c2);

    return 0;
}

void readMonkies (std::vector<Monkey> &monkies) {
    std::fstream input("Day11/input.txt");

    std::string line;
    if (input.is_open()) {
        while(std::getline(input, line)){

            //STARTING ITEMS
            std::getline(input, line);
            std::string itemString;
            std::vector<int> items;
            for (int i = 18; i < line.size(); i++){
                if (line[i] == ',') {
                    i++;
                    items.push_back(std::stoi(itemString));
                    itemString = "";
                    continue;
                }
                itemString.push_back(line[i]);
            }
            items.push_back(std::stoi(itemString));

            //OPERATION
            std::getline(input, line);
            std::string operation;
            for (int i = 23; i < line.size(); i++)
                operation.push_back(line[i]);

            //DIVISOR
            std::getline(input, line);
            std::string divisorString;
            for (int i = 21; i < line.size(); i++)
                divisorString.push_back(line[i]);
            int divisor = std::stoi(divisorString);

            //TRUE/FALSE MONKIES TARGETS
            std::getline(input, line);
            int trueTarget = std::stoi(std::string(1, line[29]));
            std::getline(input, line);
            int falseTarget = std::stoi(std::string(1, line[30]));
            std::getline(input, line);

            //ADD THE FINAL MONKEY TO THE MONKEYS LIST
            monkies.push_back(Monkey(operation, divisor, trueTarget, falseTarget));

            //GIVE THE MONKEY ITS ITEMS
            for (int item: items)
                monkies[monkies.size() - 1].giveItem(item);
        }
    }
}