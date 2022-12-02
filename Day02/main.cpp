#include <iostream>
#include <fstream>

int gameWithInput(char elfMove, char myMove);
int gameWithOutput(char elfMove, char result);

int main() {
    int scoreRound1 = 0, scoreRound2 = 0, c = 0;

    std::fstream input("Day02/input.txt");
    if (input.is_open()) {
        std::string line;
        while (std::getline(input, line)) {
            scoreRound1 += gameWithInput(line[0], line[2]);
            scoreRound2 += gameWithOutput(line[0], line[2]);
            c++;
        }
    }
    std::cout << "The final score from round 1 is " << scoreRound1 << " after " << c << " games" << std::endl;
    std::cout << "The final score from round 2 is " << scoreRound2;
}

int gameWithInput(char elfMove, char myMove) {
    switch (elfMove) {
        case 'A':
            switch (myMove) {
                case 'X': return 3 + 1; //rock v rock
                case 'Y': return 6 + 2; //rock v paper
                case 'Z': return 0 + 3; //rock v scissors
            }
        case 'B':
            switch (myMove) {
                case 'X': return 0 + 1; //paper v rock
                case 'Y': return 3 + 2; //paper v paper
                case 'Z': return 6 + 3; //paper v scissors
            }
        case 'C':
            switch (myMove) {
                case 'X': return 6 + 1; //scissors v rock
                case 'Y': return 0 + 2; //scissors v paper
                case 'Z': return 3 + 3; //scissors v scissors
            }
    }
    return 0;
}

int gameWithOutput(char elfMove, char result) {
    switch (elfMove) {
        case 'A':
            switch (result) {
                case 'X': return 3 + 0; //elf rock, lose (scissors)
                case 'Y': return 1 + 3; //elf rock, draw (rock)
                case 'Z': return 2 + 6; //elf rock, win (paper)
            }
        case 'B':
            switch (result) {
                case 'X': return 1 + 0; //elf paper, lose (rock)
                case 'Y': return 2 + 3; //elf paper, draw (paper)
                case 'Z': return 3 + 6; //elf paper, win (scissors)
            }
        case 'C':
            switch (result) {
                case 'X': return 2 + 0; //elf scissors, lose (paper)
                case 'Y': return 3 + 3; //elf scissors, draw (scissors)
                case 'Z': return 1 + 6; //elf scissors, win (rock)
            }
    }
    return 0;
}