//
// Created by Aaron Rucinski on 01/12/2022.
//
#include <vector>

#ifndef AOC2022_ELF_H
#define AOC2022_ELF_H


class elf
{
    std::vector<int> meals = std::vector<int>();

    public:
        int getTotalCalories(void);
        void addMeal(int calories);
};


#endif //AOC2022_ELF_H
