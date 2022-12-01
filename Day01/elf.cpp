//
// Created by Aaron Rucinski on 01/12/2022.
//

#include "elf.h"

int elf::getTotalCalories(void)
{
    int total = 0;

    for (int c: meals)
        total += c;

    return total;
}

void elf::addMeal(int calories)
{
    meals.push_back(calories);
}