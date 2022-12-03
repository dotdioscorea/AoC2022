//
// Created by Aaron Rucinski on 03/12/2022.
//
#include <String>

#ifndef AOC2022_BACKPACK_H
#define AOC2022_BACKPACK_H


class backpack {
    std::string frontCompartment = "", rearCompartment = "", common = "";

    public:
    int prioritiesSum = 0;
    backpack(std::string contents);
    std::string getItems();
    int commonItem(backpack backpack2, backpack backpack3);
};


#endif //AOC2022_BACKPACK_H
