//
// Created by Aaron Rucinski on 03/12/2022.
//

#include "backpack.h"
#include <iostream>

backpack::backpack(std::string contents) {
    for (int i = 0; i < contents.length(); i++)
        if (i < contents.length() / 2)
            frontCompartment += contents[i];
        else {
            rearCompartment += contents[i];
            for (char c: frontCompartment)
                if (c == contents[i]) {
                    bool found = false;
                    for (char c2: common)
                        if (c == c2)
                            found = true;

                    if (found)
                        break;

                    common += c;
                    if (c > 91) //lowercase
                        prioritiesSum += c - 96;
                    else //uppercase
                        prioritiesSum += c - 38;

                    break;
                }
        }
}

std::string backpack::getItems()
{
    return frontCompartment + rearCompartment;
}

int backpack::commonItem(backpack backpack2, backpack backpack3) {
    for (char c: getItems())
        for (char c2: backpack2.getItems())
            for (char c3: backpack3.getItems()) {
                if (c == c2 && c2 == c3) {
                    if (c > 91) //lowercase
                        return c - 96;
                    else //uppercase
                        return c - 38;
                }
            }
}