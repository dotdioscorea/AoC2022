//
// Created by Aaron Rucinski on 09/12/2022.
//

#include "rope.h"
#include <cmath>
#include <iostream>

//CONSTRUCTOR ADD KNOTS TO ROPE
rope::rope(int numberOfKnots) {
    for (int i = 0; i < numberOfKnots; i++)
        knots.push_back(Knot());
}

//CALL TO MOVE X STEPS IN Y DIRECTION
void rope::moveHead(char direction, int steps) {
    for (int i = 0; i < steps; i++)
        stepDirection(direction);
}

//CALLED AFTER MOVING HEAD TO MOVE EACH KNOT
void rope::updateKnots() {
    for (int i = 1; i < knots.size(); i++) {
        knots[i].oldposition = knots[i].position;
        float sqrDistance = pow(knots[i].position.x - knots[i - 1].position.x, 2) +
                            pow(knots[i].position.y - knots[i - 1].position.y, 2);

        //CASE WHEN PREVIOUS KNOT IS STILL NEIGHBORING CURRENT KNOT
        if (sqrDistance <= 2)
            continue;

        int dx = knots[i - 1].position.x - knots[i].position.x;
        int dy = knots[i - 1].position.y - knots[i].position.y;

        //CASE WHEN PREVIOUS KNOT HAS MOVED ADJACENT TO ADJACENT OR ADJACENT TO DIAGONALLY
        if (sqrDistance == 4 || sqrDistance == 8) {
            //MOVE HALF THE DISTANCE BETWEEN THE TWO KNOTS
            knots[i].position.x += dx / 2;
            knots[i].position.y += dy / 2;
        }


        //CASE WHEN PREVIOUS KNOW HAS MOVED DIAGONALLY ADJACENT OR ADJACENT DIAGONALLY
        if (sqrDistance == 5) {
            //L SHAPED MOVEMENT IS TO MOVE 1 IN THE VECTOR DIRECTION EG 2/-2 BECOMES 1/-1
            dx = (dx > 0) - (dx < 0);
            dy = (dy > 0) - (dy < 0);

            knots[i].position.x += dx;
            knots[i].position.y += dy;
        }
    }
}

//MOVE THE HEAD (AND REST OF ROPE) ONE STEP IN A DIRECTION
void rope::stepDirection(char direction) {
    knots[0].oldposition = knots[0].position;

    switch (direction) {
        case 'L':
            knots[0].position.x--;
            break;
        case 'R':
            knots[0].position.x++;
            break;
        case 'U':
            knots[0].position.y++;
            break;
        case 'D':
            knots[0].position.y--;
            break;
    }

    updateKnots();
    addTailPosition();
    //printMap();
}

//USED TO RECORD TAIL POSITIONS WITHOUT DUPES
void rope::addTailPosition() {
    for (Position p: tailPositions)
        if (p.x == knots[knots.size() - 1].position.x && p.y == knots[knots.size() - 1].position.y)
            return;
    tailPositions.push_back(knots[knots.size() - 1].position);
}

//PRINTS A MAP OF THE ROPE EACH MOVEMENT. FOR DIAGNOSTICS
void rope::printMap() {
    int size = 20;
    for (int y = size - 1; y >-15; y--) {
        for (int x = -15; x < size; x++) {
            bool ropeHere = false;
            for (int i = 0; i < knots.size(); i++)
                if (knots[i].position.x == x && knots[i].position.y == y) {
                    std::cout << 1 + i;
                    ropeHere = true;
                    break;
                }
            if (!ropeHere)
                std::cout << ".";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}