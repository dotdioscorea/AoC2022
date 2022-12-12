#include <iostream>
#include <fstream>
#include <vector>

struct position { int x; int y; };

position neighbors[4] {position{-1, 0},
                       position{1, 0},
                       position{0, 1},
                       position{0, -1}};

void getDimensions(int &width, int &height);
void readInput (char **heightMap, int **nodeMap, std::vector<position> &newNodes, position &endPoint, int &width, int &height);
bool dijkstraCycle (char **heightMap, int **nodeMap, std::vector<position> &newNodes, position &endPoint, int &width, int &height, int &shortestPath, int direction);

int main() {
    //GET DIMENSIONS OF MAP
    int width = 179;
    int height = 41;
    getDimensions(width, height);

    //POPULATE ARRAYS
    char **heightMap = (char **) calloc(width, sizeof(char *));
    int **nodeMap = (int **) calloc(width, sizeof(int *));
    for (int i = 0; i < width; i++) {
        heightMap[i] = (char *) calloc(height, sizeof(char));
        nodeMap[i] = (int *) calloc(height, sizeof(int));
    }
    position endPoint;
    std::vector<position> newNodes;
    int shortestPath;
    readInput(heightMap, nodeMap, newNodes, endPoint, width, height);

    //PERFORM PART 1 ALGORITHM
    while(true)
        if(dijkstraCycle(heightMap, nodeMap, newNodes, endPoint, width, height, shortestPath, 0))
            break;
    std::cout << "Found route with length " << shortestPath << std::endl;

    //RESET NODE ARRAY (DUNNO WHY MEMSET NOT WORKING HERE)
    for (int y = height - 1; y >= 0; y--)
        for (int x = 0; x < width; x++)
            nodeMap[x][y] = -1;
    //SET START POINT TO PREVIOUS END POINT
    nodeMap[endPoint.x][endPoint.y] = 0;
    newNodes.clear();
    newNodes.push_back(position{endPoint.x, endPoint.y});

    //REPEAT ALGORITHM WORKING BACKWARDS FROM START
    while(true)
        if(dijkstraCycle(heightMap, nodeMap, newNodes, endPoint, width, height, shortestPath, 1))
            break;
    std::cout << "Shortest A route is " << shortestPath - 1;

    return 0;
}

bool dijkstraCycle(char **heightMap, int **nodeMap, std::vector<position> &newNodes, position &endPoint, int &width, int &height, int &shortestPath, int direction) {
    std::vector<position> newnewNodes;

    for (position p: newNodes) {
        //CHECK NEIGHBORS
        for (position n: neighbors) {
            //OUT OF BOUNDS CASE
            if (p.x + n.x < 0 ||
                p.x + n.x > width - 1 ||
                p.y + n.y < 0 ||
                p.y + n.y > height - 1)
                continue;

            //CHECK NODE NEIGHBOUR ELIGIBILITY
            if (nodeMap[p.x + n.x][p.y + n.y] != -1)
                continue;

            //CHECK IF SAME LETTER OR +1
            if (direction == 0)
                if (heightMap[p.x + n.x][p.y + n.y] - heightMap[p.x][p.y] > 1)
                    continue;
            if (direction == 1)
                if (heightMap[p.x][p.y] - heightMap[p.x + n.x][p.y + n.y] > 1)
                    continue;

            //NODE ELIGIBLE
            newnewNodes.push_back(position{p.x + n.x, p.y + n.y});

            //GET SMALLEST VALUE AVAILABLE AND SET
            int value = nodeMap[p.x][p.y] + 1;
            for (position n2: neighbors) {
                //OUT OF BOUNDS CASE PREVENTION
                if (p.x + n.x + n2.x < 0 ||
                    p.x + n.x + n2.x > width - 1 ||
                    p.y + n.y + n2.y < 0 ||
                    p.y + n.y + n2.y > height - 1)
                    continue;

                //CHECK IF SAME LETTER OR +1
                if (direction == 0)
                    if (heightMap[p.x + n.x][p.y + n.y] - heightMap[p.x + n.x + n2.x][p.y + n.y + n2.y] > 1)
                        continue;
                if (direction == 1)
                    if (heightMap[p.x + n.x + n2.x][p.y + n.y + n2.y] - heightMap[p.x + n.x][p.y + n.y] > 1)
                        continue;

                //CHECK IF NEIGHBOUR NODE'S NEIGHBOURS ARE UNSET, AND FOR LOWER VALUE
                if (nodeMap[p.x + n.x + n2.x][p.y + n.y + n2.y] != -1 &&
                    nodeMap[p.x + n.x + n2.x][p.y + n.y + n2.y] + 1 < value)
                    value = nodeMap[p.x + n.x + n2.x][p.y + n.y + n2.y] + 1;
            }
            nodeMap[p.x + n.x][p.y + n.y] = value;

            //HANDLE FINISHED CASE
            if (direction == 0)
                if (p.x + n.x == endPoint.x && p.y + n.y == endPoint.y) {
                    shortestPath = value;
                    return true;
                }
            if (direction == 1)
                if (heightMap[p.x][p.y] == 'a') {
                    shortestPath = value;
                    return true;
                }
        }
    }
    newNodes = newnewNodes;
    return false;
}

void getDimensions(int &width, int &height) {
    //PREPARE VARIABLES
    std::fstream input("Day12/input.txt");
    if (!input.is_open())
        return;
    std::string line;

    //SETUP DIMENSIONS
    width = line.size();
    height = 0;
    //FIRST PASS RUN TO GET HEIGHT OF MAP
    while (std::getline(input, line)) height++;
}

void readInput (char **heightMap, int **nodeMap, std::vector<position> &newNodes, position &endPoint, int &width, int &height) {
    //PREPARE VARIABLES
    std::fstream input("Day12/input.txt");
    if (!input.is_open())
        return;
    std::string line;
    std::getline(input, line);

    //POPULATE ARRAYS
    int x = 0, y = height - 1;
    while (y >= 0) {
        for (char c: line) {
            //FIND START POS
            if (c == 'S') {
                //SET START VALUE TO 'Z' SO ALGORITHM WORKS
                c = 'a';
                newNodes.push_back(position{x, y});
                //START POS HAS NODE VALUE 0
                nodeMap[x][y] = 0;
            }
            else
                nodeMap[x][y] = -1; //UNCHECKED NODES ARE -1

            //FIND END POS
            if (c == 'E') {
                endPoint = position{x, y};
                //SET END VALUE TO 'Z' SO ALGORITHM WORKS
                c = 'z';
            }

            heightMap[x][y] = c;
            x++;
        }
        y --;
        x = 0;
        std::getline(input, line);
    }
    return;
}