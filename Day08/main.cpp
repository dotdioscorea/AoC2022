#include <iostream>
#include <fstream>
#include <ios>
#include <map>

bool** findVisibleTrees(int** treeHeights, int width, int height);
int** findScenicScores(int** treeHeights, int width, int height);

int main() {
    std::fstream input("Day08/input.txt");
    int width = 0, height = 0;
    int **treeHeights; //TREE HEIGHTS ARRAY POINTER FOR ACCESSING LATER

    if (input.is_open()) {
        std::string line;

        //FIRST PASS RUN TO GET FOREST DIMENSIONS
        if (std::getline(input, line)) { height++; width = (int) line.size(); }
        while (std::getline(input, line)) height++;
        //RESET F STREAM TO BEGINNING AND CLEAR EOF
        input.clear();
        input.seekg(0, std::ios::beg);

        //ALLOCATE ARRAYS FOR TREE HEIGHT AND VISIBILITY
        treeHeights = (int **) calloc(width, sizeof(int *));
        for (int i = 0; i < height; i++)
            treeHeights[i] = (int *) calloc(height, sizeof(int));

        //POPULATE ARRAY WITH TREE HEIGHTS (SECOND PASS AT FILE)
        int y = 0;
        while (std::getline(input, line)) {
            for (int x = 0; x < width; x++)
                treeHeights[x][y] = line[x] - 48;
            y++;
        }
    } else return 1;

    //PART 1 - POPULAR A VISIBILITY ARRAY
    bool** forestVisibility = findVisibleTrees(treeHeights, width, height);

    //COUNT VISIBLE TREES
    int c = 2 * (width + height) - 4;
    for (int y = 1; y < height - 1; y++)
        for (int x = 1; x < width - 1; x++)
            if (forestVisibility[x][y])
                c++;

    std::cout << "Number of visible trees is " << c;

    //PART 2 - POPULAR A SCENIC SCORES ARRAY
    int** scenicScores = findScenicScores(treeHeights, width, height);

    //FIND MOST SCENIC TREE
    int mostScenic = 0;
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            if (scenicScores[x][y] > mostScenic)
                mostScenic = scenicScores[x][y];

    std::cout << std::endl << "Most scenic tree has a value of " << mostScenic;

    return 0;
}

bool** findVisibleTrees(int** treeHeights, int width, int height){
    //PART 1 - OKAY, THIS METHOD DID NOT HELP WITH PART 2, BUT IT'S THE FASTEST
    // COMPUTATIONALLY (DON'T HAVE TO CHECK EVERY TREE THIS WAY)

    //ALLOCATE VISIBILITY ARRAY
    bool** forestVisibility = (bool **) calloc(width, sizeof(bool *));
    for (int i = 0; i < height; i++)
        forestVisibility[i] = (bool *) calloc(height, sizeof(bool));

    //COUNT FROM TOP
    for (int x = 1; x < width - 1; x++)
        for (int y = 1; y < height - 1; y++)
            if (!forestVisibility[x][y]) {
                forestVisibility[x][y] = true;
                for (int y2 = y - 1; y2 >= 0; y2--)
                    if (treeHeights[x][y] <= treeHeights[x][y2]) { forestVisibility[x][y] = false; break; }
            }

    //COUNT FROM BOTTOM
    for (int x = 1; x < width - 1; x++)
        for (int y = height - 2; y >= 1; y--)
            if (!forestVisibility[x][y]) {
                forestVisibility[x][y] = true;
                for (int y2 = y + 1; y2 < height; y2++)
                    if (treeHeights[x][y] <= treeHeights[x][y2]) { forestVisibility[x][y] = false; break; }
            }

    //COUNT FROM LEFT
    for (int y = 1; y < height - 1; y++)
        for (int x = 1; x < width - 1; x++)
            if (!forestVisibility[x][y]) {
                forestVisibility[x][y] = true;
                for (int x2 = x - 1; x2 >= 0; x2--)
                    if (treeHeights[x][y] <= treeHeights[x2][y]) { forestVisibility[x][y] = false; break; }
            }

    //COUNT FROM RIGHT
    for (int y = 1; y < height - 1; y++)
        for (int x = width - 2; x >= 1; x--)
            if (!forestVisibility[x][y]) {
                forestVisibility[x][y] = true;
                for (int x2 = x + 1; x2 < width; x2++)
                    if (treeHeights[x][y] <= treeHeights[x2][y]) { forestVisibility[x][y] = false; break; }
            }

    return forestVisibility;
}

int** findScenicScores(int** treeHeights, int width, int height){
    //ALLOCATE ARRAY
    int** scenicScores = (int **) calloc(width, sizeof(int *));
    for (int i = 0; i < height; i++)
        scenicScores[i] = (int *) calloc(height, sizeof(int));

    //ITERATE THROUGH EVERY TREE
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++) {
            int scoreXL = 0, scoreXR = 0, scoreYU = 0, scoreYD = 0;

            //CHECK LEFT X ROW
            for (int x2 = x - 1; x2 >= 0; x2--)
                if (treeHeights[x][y] > treeHeights[x2][y])
                    scoreXL++;
                else {
                    scoreXL++;
                    break;
                }

            //CHECK RIGHT X ROW
            for (int x2 = x + 1; x2 < width; x2++)
                if (treeHeights[x][y] > treeHeights[x2][y])
                    scoreXR++;
                else {
                    scoreXR++;
                    break;
                }

            //CHECK UPWARDS Y COLUMN
            for (int y2 = y - 1; y2 >= 0; y2--)
                if (treeHeights[x][y] > treeHeights[x][y2])
                    scoreYU++;
                else {
                    scoreYU++;
                    break;
                }

            //CHECK DOWNWARDS Y COLUMN
            for (int y2 = y + 1; y2 < height; y2++)
                if (treeHeights[x][y] > treeHeights[x][y2])
                    scoreYD++;
                else {
                    scoreYD++;
                    break;
                }

            scenicScores[x][y] = scoreXL * scoreXR * scoreYD * scoreYU;
        }

    return scenicScores;
}