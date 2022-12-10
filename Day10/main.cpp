#include <iostream>
#include <fstream>
#include <ios>
#include <map>

bool readInstruction(std::fstream *input, char *instruction, int *parameter);
void executeInstruction(int *clock, int *reg, int* summer, char *instruction, int *parameter);
void cycleSummer(int *clock, int *reg, int* summer);
void drawCRT(int *clock, int *reg);

int main() {
    std::fstream input("Day10/input.txt");

    //INITIALISE VARIABLES
    int clock = 0, reg = 1, summer = 0, parameter;
    char instruction;

    //READ AND EXECUTE INSTRUCTIONS
    while (readInstruction(&input, &instruction, &parameter))
        executeInstruction(&clock, &reg, &summer, &instruction, &parameter);

    std::cout << std::endl << std::endl << "Final value of summer is " << std::to_string(summer);

    return 0;
}

void executeInstruction(int *clock, int *reg, int* summer, char *instruction, int *parameter) {
    //BEGIN CLOCK CYCLE
    *clock += 1;
    //FOR PART 1
    cycleSummer(clock, reg, summer);
    //FOR PART 2
    drawCRT(clock, reg);

    //NOOP COMMAND, ONLY ONE CLOCK CYCLE
    if (*instruction == 'n')
        return;

    //SECOND CLOCK CYCLE IF ADDX COMMAND
    *clock += 1;
    //FOR PART 1
    cycleSummer(clock, reg, summer);
    //FOR PART 2
    drawCRT(clock, reg);

    //END OF ADDX, EXECUTION COMPLETES
    *reg += *parameter;
}

void drawCRT(int *clock, int *reg) {
    //GET CURRENT X PIXEL LOCATION
    int pixelX = *clock % 40 - 1;

    //NEW LINE PRINT HANDLE
    if (*clock % 40 == 1)
        std::cout << std::endl;

    //CHECK IF WITHIN 1 OF SPRITE (3x1 SPRITE SIZE)
    if (abs(pixelX - *reg) <= 1)
        std::cout << "#";
    else
        std::cout << ".";
}

//PART 1
void cycleSummer(int *clock, int *reg, int* summer) {
    if ((*clock + 20) % 40 == 0)
        *summer += *reg * *clock;
}

//BORING FILE READING STUFF
bool readInstruction(std::fstream *input, char *instruction, int *parameter) {
    std::string line;
    if (!(input->is_open() && std::getline(*input, line)))
        return false;

    *instruction = line[0];
    if (*instruction == 'n')
        return true;

    std::string parameterString;
    for (int i = 5; i < line.size(); i++)
        parameterString.push_back(line[i]);
    *parameter = std::stoi(parameterString);

    return true;
}

