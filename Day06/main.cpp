#include <iostream>
#include <fstream>

int findDupes(int sequenceLength, std::string &line);

int main() {
    std::fstream input("Day06/input.txt");
    if (input.is_open()) {
        std::string line;
        std::getline(input, line);

        std::cout << "The packet starts at position " << std::to_string(findDupes(4, line) + 1) << std::endl;
        std::cout << "The message starts at position " << std::to_string(findDupes(14, line) + 1);

        return 0;
    }
}

int findDupes(int sequenceLength, std::string &line) {
    //Check each character in the message, starting at earliest possible point
    for (uint32_t i = sequenceLength; i < line.size(); i++) {
        bool dupeFound = false;

        //Start checking front character for dupes
        for (int j = 0; j < sequenceLength; j++) {
            //Compare with each character remaining behind front character
            for (int k = 1; k < sequenceLength - j; k++) {
                if (line[i - j] == line[i - j - k]) {
                    //Check the flag if dupe found, this ith character is a nogo
                    dupeFound = true;
                    break;
                }
            }
            //Saves unnecessary looping
            if(dupeFound)
                break;
        }

        //When answer found (eg flag not set)
        if(!dupeFound)
            return i;
    }
    //No dupes found error
    return -1;
}