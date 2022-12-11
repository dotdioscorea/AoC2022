//
// Created by Aaron Rucinski on 11/12/2022.
//
#include <vector>

#ifndef AOC2022_MONKEY_H
#define AOC2022_MONKEY_H

class Monkey {
public:
    Monkey(std::string _operation, int _divisor, int _trueTarget, int _falseTarget);
    void giveItem(uint64_t item);
    void cycleMonkey(std::vector<Monkey> &monkies);
    uint32_t timesInspected; //INCREMENTED EACH INSPECTION OF AN ITEM
private:
    void inspectItems(std::vector<Monkey> &monkies);
    void throwItems(std::vector<Monkey> &monkies);

    std::vector<uint64_t> items;
    int operation = 0; //0 IS ADDITION, 1 IS MULTIPLICATION
    int value = 0; //0 IS ODD, 1 IS A NUMBER
    int divisor = 1; //EACH MONKEY'S DIVISOR
    int trueTarget; //TARGET IF DIVISOR TRUE
    int falseTarget; //TARGET IF DIVISOR FALSE
};


#endif //AOC2022_MONKEY_H
