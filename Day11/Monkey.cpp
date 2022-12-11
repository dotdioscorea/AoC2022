//
// Created by Aaron Rucinski on 11/12/2022.
//

#include <string>
#include "Monkey.h"

#define part1
//#define part2

Monkey::Monkey(std::string _operation, int _divisor, int _trueTarget, int _falseTarget) {

    //SET VALUE, DEFAULT IS TO USE OLD
    if (_operation[2] != 'o') {
        std::string valueString;
        for (int i = 2; i < _operation.size(); i++)
            valueString.push_back(_operation[i]);

        value = std::stoi(valueString);
    }

    //SET VALUE, DEFAULT IS ADDITION
    if (_operation[0] == '*')
        operation = 1;

    //SET DIVISOR
    divisor = _divisor;

    trueTarget = _trueTarget;
    falseTarget = _falseTarget;
    timesInspected = 0;
}

//GIVE MONKEY AN ITEM
void Monkey::giveItem(uint64_t item) {
    items.push_back(item);
}

//MONKEY INSPECTS ITEMS AND ANXIETY LEVEL CHANGES (ALSO MANAGES LARGE VALUES)
void Monkey::inspectItems(std::vector<Monkey> &monkies) {

#ifdef part2
    uint64_t megaMod = 1;
    for (Monkey monkey: monkies)
        megaMod *= monkey.divisor;
#endif

    for (int i = 0; i < items.size(); i++) {
        operation == 0 ? items[i] += (value == 0 ? items[i] : value) : items[i] *= (value == 0 ? items[i] : value);
#ifdef part1
        items[i] /= 3;
#endif
#ifdef part2
        items[i] %= megaMod;
#endif
        timesInspected += 1;
    }
}

//CALLED FROM MAIN TO PERFORM A MONKEY CYCLE, HANDLES INSPECTING AND THROWING
void Monkey::cycleMonkey(std::vector<Monkey> &monkies) {
    inspectItems(monkies);
    throwItems(monkies);
}

//CALLED FROM MONKEY CYCLE FUNCTION, HANDLES THROWING, ALSO REMOVES FROM CURRENT MONKEY
void Monkey::throwItems(std::vector<Monkey> &monkies) {
    for (int i = 0; i < items.size(); i++)
        if (items[i] % divisor == 0)
            monkies[trueTarget].giveItem(items[i]);
        else
            monkies[falseTarget].giveItem(items[i]);

    //RESET MONKEY'S ITEMS
    items.clear();
}