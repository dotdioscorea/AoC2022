#include <iostream>
#include <fstream>
#include <vector>

bool getNextPackets(std::fstream &input, std::string &packetA, std::string &packetB);
bool isArray(std::string string);
void compareArrays(std::vector<std::string> arrayA, std::vector<std::string> arrayB, int &result);
bool comparePackets(std::string packetA, std::string packetB);
std::vector<std::string> getItemsInArray(std::string array);

int main() {
    std::fstream input("Day13/input.txt");
    std::string packetA, packetB;
    std::vector<std::string> allPackets;

    //PART 1
    int sum = 0, packetNumber = 0;
    while (getNextPackets(input, packetA, packetB)) {
        packetNumber++;
        //STORE FOR LATER
        allPackets.push_back(packetA);
        allPackets.push_back(packetB);

        //COMPARE PACKETS
        if (comparePackets(packetA, packetB))
            sum += packetNumber;

        //HANDLE BLANK LINE BETWEEN PACKET PAIRS
        std::getline(input, packetA);
    }
    std::cout << "Sum of correct packet orders is " << sum << std::endl;

    //PART 2
    allPackets.push_back("[[2]]");
    allPackets.push_back("[[6]]");

    //SORT THE VECTOR LIST
    std::sort(allPackets.begin(), allPackets.end(), comparePackets);

    //FIND THE DIVIDER PACKETS AND KEY
    int key = 0;
    for (int i = 0; i < allPackets.size(); i++)
        if (allPackets[i] == "[[2]]")
            key += i + 1;
        else if (allPackets[i] == "[[6]]")
            key *= i + 1;

    std::cout << "Decoder key is " << key;
}

//COMPARES TWO PACKETS, RETURNING IF THEY ARE IN ORDER
bool comparePackets(std::string packetA, std::string packetB) {
    int result = 0; //1=TRUE; 2=FALSE; 0=NOT FOUND YET (MUST NEVER RETURN 0)
    compareArrays(getItemsInArray(packetA), getItemsInArray(packetB), result);
    return result == 1;
}

//COMPARES ITEMS IN ARRAY, RETURN TRUE IF IN CORRECT ORDER
void compareArrays(std::vector<std::string> arrayA, std::vector<std::string> arrayB, int &result) {
    //MOVE THROUGH EACH ITEM IN ARRAY
    for (int i = 0; i < arrayA.size(); i++) {
        //CHECK IF PREVIOUS RUN HAS FOUND ANSWER
        if (result != 0)
            break;

        //CHECK THAT CURRENT A POSITION SMALLER THAN B
        if (i > arrayB.size() - 1) { result = 2; break; }

        //CHECK FOR EMPTY ARRAY CONDITIONS
        if (arrayA[i].size() == 0)
            //IF BOTH EMPTY, CONTINUE AS PER RULES
            if (arrayB[i].size() == 0)
                continue;
            //IF A EMPTY FIRST THEN CORRECT ORDER
            else { result = 1; break; }
        //IF B EMPTY THEN WRONG ORDER
        if (arrayB[i].size() == 0) { result = 2; break;}

        //BOTH INTEGERS
        if (!isArray(arrayA[i]) && !isArray(arrayB[i]))
            if (std::stoi(arrayA[i]) > std::stoi(arrayB[i])) { result = 2; break; }
            else if (std::stoi(arrayA[i]) < std::stoi(arrayB[i])) { result = 1; break; }
            else continue; //A == B CASE


        //OTHERWISE COMPARE AS ARRAYS AND GO DEEPER
        compareArrays(getItemsInArray(arrayA[i]), getItemsInArray(arrayB[i]), result);
    }
    //CATCH IF A ARRAY HAS FINISHED, BUT DO NOT OVERRIDE A DEEPER FALSE RESULT
    if (result == 0 && arrayB.size() > arrayA.size())
        result = 1;
}

//RETURNS A LIST OF STRINGS IN A STRING ARRAY
std::vector<std::string> getItemsInArray(std::string array) {
    std::vector<std::string> items;

    //IF INT SHORTCUT
    if (!isArray(array)) { items.push_back(array); return items; }

    //SEPARATE STRING BY (,) AND EXCLUDE OUTER BRACKETS
    std::string temp;
    int depth = 0;
    for (int i = 1; i < array.size() - 1; i++) {
        //AVOID BREAKING UP ON SUB ARRAYS
        if (array[i] == '[') depth++;
        if (array[i] == ']') depth--;
        //BREAK ON ARRAY DIVISOR
        if (array[i] == ',' && depth == 0) {
            items.push_back(temp);
            temp.clear();
        }
        else temp.push_back(array[i]);
    }
    //GET LAST VALUE TOO
    items.push_back(temp);

    return items;
}

//CHECK IF A STRING IS AN ARRAY (EG NOT INT)
bool isArray(std::string string) {
    return string[0] == '[' ? true : false;
}

//RETREIVE NEXT PACKET PAIR FROM FILE
bool getNextPackets(std::fstream &input, std::string &packetA, std::string &packetB) {
    return (input.is_open() && std::getline(input, packetA) && std::getline(input, packetB));
}