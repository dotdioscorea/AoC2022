#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::vector<std::vector<char>> stacks1;
    std::vector<std::vector<char>> stacks2;

    std::fstream input("Day05/input.txt");
    if (input.is_open()) {
        std::string line;
        while (std::getline(input, line)) {
            //Setup stacks
            if (stacks1.size() == 0)
                for (int i = 0; i < (line.length() + 1) / 4; i++)
                    stacks1.push_back(std::vector<char>());

            //Get numbers
            if (line[0] == '[') {
                for (int i = 0; i < line.size(); i++)
                    if (line[i] == '[')
                        stacks1[(i / 4)].insert(stacks1[(i / 4)].begin(), line[i + 1]);
                stacks2 = std::vector<std::vector<char>>(stacks1);
            }

            //Process instructions
            if (line[0] == 'm') {
                //Get instructions number variables
                int num = 0, origin = 0, target = 0;
                std::string temp = "";

                //Get each chain of number chars
                for (int i = 0; i < line.size(); i++) {
                    while (line[i] >= 48 && line[i] <= 57) {
                        temp += line[i];
                        i++;
                    }

                    //If non numbers so far, skip stoi
                    if (temp == "")
                        continue;

                    //Convert chain of number chars to int
                    if (num == 0)
                        num = std::stoi(temp);
                    else if (origin == 0)
                        origin = std::stoi(temp);
                    else
                        target = std::stoi(temp);

                    //Reset
                    temp = "";
                }

                //Process instructions
                for (int i = 0; i < num; i++) {
                    //Process stacks for part 1
                    stacks1[target - 1].push_back(stacks1[origin - 1].back());
                    stacks1[origin - 1].pop_back();

                    //Process tacks for part 2
                    stacks2[target - 1].push_back(stacks2[origin - 1][stacks2[origin - 1].size() - num + i]);
                    stacks2[origin - 1].erase(stacks2[origin - 1].end() - num + i);
                }
            }
        }

        //Print answers
        std::cout << "For the first crane, the top elements of each stack are ";
        for (std::vector<char> stack: stacks1)
            std::cout << stack[stack.size() - 1];

        std::cout << std::endl << "For the second crane, the top elements of each stack are ";
        for (std::vector<char> stack: stacks2)
            std::cout << stack[stack.size() - 1];
    }
}