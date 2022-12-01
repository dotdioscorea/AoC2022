#include <iostream>
#include <fstream>
#include <vector>
#include "elf.h"

int main() {
    std::vector<elf> elves;

    std::fstream input ("Day01/input.txt");
    if(input.is_open())
    {
        elves.push_back(elf()); //The first elf

        std::string line;
        while(std::getline(input, line))
        {
            //If the line is empty, then it indicates a new elf
            if (line.length() == 0) {
                elves.push_back(elf());
                continue;
            }
            //Otherwise the meal belongs to the most recent elf
            else {
                elves[elves.size() - 1].addMeal(std::stoi(line));
            }
        }
    }

    std::cout << "Imported " << elves.size()  << " elves." << std::endl;

    //For each elf request its total calorie count and place in totals where appropriate
    int high_calories = 0;
    std::vector<int> calories;

    for (elf e:elves)
    {
        int c = e.getTotalCalories();
        if (c > high_calories)
            high_calories = c;
        calories.push_back(c);
    }
    std::sort(calories.begin(), calories.end(), std::greater<int>());

    std::cout << "Highest calorie count found was " << high_calories << " calories." << std::endl;
    if (calories.size() >= 3)
        std::cout << "Top three elves were holding " << calories[0] + calories[1] + calories[2] << " calories.";

    return 0;
}
