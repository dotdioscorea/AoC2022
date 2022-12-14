#include <iostream>
#include <fstream>
#include <vector>
#include "resources.h"

//#define part2

bool readNextRock(std::fstream &input, std::vector<rock> &rocks, position &minP, position &maxP);
char** readAllRocks(position &mapDimensions, position &sandSource);
void addRockToMap(char** map, rock r);
sand newSand(char** map, position sandSource);
bool moveSand(char** map, sand &currentSand, char direction);
bool updateSand(char** map, position mapDimensions, sand &currentSand, position sandSource);
void printMap(char** map, position mapDimensions);
int countSand (char** map, position &mapDimensions);

int main() {
    position mapDimensions, sandSource {500, 0};
    //INITIALIZE MAP
    char** map = readAllRocks(mapDimensions, sandSource);
    //INITIAL SAND
    sand currentSand = newSand(map, sandSource);
    //KEEP SAND FALLING UNTIL FINISHED
    while (updateSand(map, mapDimensions, currentSand, sandSource))
        continue;
    //PRINT OUTPUT
    std::cout << "Number of sands: " << countSand(map, mapDimensions);
}

//COUNT NUMBER OF SANDS ON MAP
int countSand (char** map, position &mapDimensions) {
    int n = 0;
    for (int y = 0; y <= mapDimensions.y; y++)
        for (int x = 0; x <= mapDimensions.x; x++)
            if (map[x][y] == 'x' || map[x][y] == '+')
                n++;
    //REQUIRED DUE TO IM NOT SURE WHAT LOL
#ifdef part2
    n++;
#endif
    return n - 1;
}

//MOVE SAND IN EITHER DOWN (d), DOWN-LEFT (l), DOWN-RIGHT (r)
bool moveSand(char** map, sand &currentSand, char direction) {
    //CLEAR PREVIOUS SAND POSITION
    map[currentSand.position.x][currentSand.position.y] = '.';

    //HANDLE NEW SAND
    switch (direction) {
        case 'd':
            map[currentSand.position.x][currentSand.position.y + 1] = 'x';
            currentSand.position.y += 1;
            break;
        case 'l':
            map[currentSand.position.x - 1][currentSand.position.y + 1] = 'x';
            currentSand.position.x -= 1;
            currentSand.position.y += 1;
            break;
        case 'r':
            map[currentSand.position.x + 1][currentSand.position.y + 1] = 'x';
            currentSand.position.x += 1;
            currentSand.position.y += 1;
            break;
    }
}

//USED FOR DIAGNOSTICS
void printMap(char** map, position mapDimensions) {
    for (int y = 0; y <= mapDimensions.y; y++) {
        for (int x = 0; x <= mapDimensions.x; x++)
            std::cout << map[x][y];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//CALLED TO CHECK FOR, AND EXECUTE, ANY PENDING SAND MOVEMENT
bool updateSand(char** map, position mapDimensions, sand &currentSand, position sandSource) {
    //MAP BORDERS CASE
    if (currentSand.position.y == mapDimensions.y ||
    (currentSand.position.x == 0 && map[currentSand.position.x][currentSand.position.y + 1] != '.') ||
            (currentSand.position.x == mapDimensions.x - 1 && map[currentSand.position.x][currentSand.position.y + 1] != '.'))
        return false;

    //THREE RULES IN ORDER
    if (map[currentSand.position.x][currentSand.position.y + 1] == '.')
        moveSand(map, currentSand, 'd');
    else if (map[currentSand.position.x - 1][currentSand.position.y + 1] == '.')
        moveSand(map, currentSand, 'l');
    else if (map[currentSand.position.x + 1][currentSand.position.y + 1] == '.')
        moveSand(map, currentSand, 'r');
    else
        //PART 2 END CASE
        if (currentSand.position.x == sandSource.x && currentSand.position.y == sandSource.y) {
            map[currentSand.position.x][currentSand.position.y] = 'x';
            return false;
        }
        //OTHERWISE SAND IS SETTLED, SPAWN NEW SAND
        else
            currentSand = newSand(map, sandSource);
    return true;
}

//SPAWN A NEW SAND
sand newSand(char** map, position sandSource) {
    sand newSand{sandSource};
    map[sandSource.x][sandSource.y] = '+';
    return newSand;
}

//IMPORT ROCKS FROM INPUT FILE
char** readAllRocks(position &mapDimensions, position &sandSource) {
    std::fstream input("Day14/input.txt");
    //DEFAULT MAP SIZE 1X1
    position minP = position{500, 0};
    position maxP = position{500, 0};

    std::vector<rock> rocks;
    //GET ALL ROCK VERTICES IN PAIRS AS STRIPS
    while(readNextRock(input, rocks, minP, maxP))
        continue;
    int dX = abs(maxP.x - minP.x);
    int dY = abs(maxP.y - minP.y);

#ifdef part2
    //ADD A FLOOR AND UPDATE MIN/MAXES AND DX/DY IF APPLICABLE
    rocks.push_back(rock{
        position{ minP.x - (dY + 3), maxP.y + 2},
        position{ maxP.x + (dY + 3), maxP.y + 2}
    });
    minP.x -= dY + 3;
    maxP.x += dY + 3;
    maxP.y += 2;

    dX = abs(maxP.x - minP.x);
    dY = abs(maxP.y - minP.y);
#endif

    //NORMALIZE VALUES FOR EASIER THINKING
    for (int i = 0; i < rocks.size(); i++) {
        rocks[i].start.x -= minP.x;
        rocks[i].end.x -= minP.x;
    }
    sandSource.x -= minP.x;

    //SETUP MAP ARRAYS
    char** map = new char* [dX + 1];
    for (int x = 0; x <= dX; x++) {
        map[x] = new char[dY + 1];
        memset(map[x], '.', sizeof(char[dY + 1]));
    }

    //ADD READ ROCK STRIPS TO MAP
    for (rock r: rocks)
        addRockToMap(map, r);

    //USED FOR LATER
    mapDimensions = position{dX, dY};

    return map;
}

//ADD ROCKS TO MAPS BY STRIPS
void addRockToMap(char** map, rock r) {
    if (r.start.y == r.end.y) {
        int direction = (r.end.x - r.start.x) / abs(r.end.x - r.start.x);
        for (int x = r.start.x; x != r.end.x; x += direction)
            map[x][r.start.y] = '#';
    }
    else if (r.start.x == r.end.x) {
        for (int y = r.start.y; y != r.end.y; y += ((r.end.y - r.start.y) / abs(r.end.y - r.start.y)))
            map[r.start.x][y] = '#';
    }
    map[r.end.x][r.end.y] = '#';
}

//RETRIEVE NEXT PACKET PAIR FROM FILE
bool readNextRock(std::fstream &input, std::vector<rock> &rocks, position &minP, position &maxP) {
    std::string line;

    //READ A POSITION INTO POS2, THEN READ A NEW POS2 AND SHIFT POS2 TO POS1
    position pos1;
    position pos2;
    if (input.is_open() && std::getline(input, line)) {
        std::string temp;
        for (int i = 0; i < line.size(); i++) {
            //READ NUMBERS
            if (line[i] >= 48 && line[i] <= 57)
                temp.push_back(line[i]);
            //READ X COORDINATE
            if (line[i] == ',') {
                pos2.x = std::stoi(temp);
                if (pos2.x < minP.x) minP.x = pos2.x;
                if (pos2.x > maxP.x) maxP.x = pos2.x;

                temp.clear();
                continue;
            }
            //READ Y COORDINATE AND SHUFFLE POSITION VALUES UP ONE
            else if ((line[i] == ' ' || i == line.size() - 1) && pos2.x > 0) {
                pos2.y = std::stoi(temp);
                if (pos2.y < minP.y) minP.y = pos2.y;
                if (pos2.y > maxP.y) maxP.y = pos2.y;

                //HANDLES FIRST VALUE OF LINE
                if (pos1.x > 0)
                    rocks.push_back(rock{pos1, pos2});

                pos1 = pos2;
                pos2 = position{-1, -1};

                temp.clear();
                continue;
            }
        }
        return true;
    }
    return false;
}