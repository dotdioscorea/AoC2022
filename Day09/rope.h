//
// Created by Aaron Rucinski on 09/12/2022.
//
#include <vector>

#ifndef AOC2022_ROPE_H
#define AOC2022_ROPE_H

struct Position{
    int x = 1;
    int y = 1;
};

bool operator +(const Position& x, const Position& y) {
    return std::tie(x.x, x.y) + std::tie(y.x, y.y);
}

struct Knot{
    Position position;
    Position oldposition;
};

class rope {
public:
    rope(int numberOfKnots);
    void moveHead(char direction, int steps);
    std::vector<Position> tailPositions;

private:
    void updateKnots();
    void stepDirection(char direction);
    std::vector<Knot> knots;
    void addTailPosition();
    void printMap();
};


#endif //AOC2022_ROPE_H
