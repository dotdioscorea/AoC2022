#include <iostream>
#include <fstream>

int main() {
    int totalOverlaps = 0;
    int partialOverlaps = 0;

    std::fstream input("Day04/input.txt");
    if (input.is_open()) {
        std::string line;
        while (std::getline(input, line)) {

            //Split string on non digit characters
            std::string s = "";
            int nums[4], n = 0;
            for (char c: line)
                //If not a digit, then cast to int and begin next number
                if (!(c >= 48 && c <= 57)) {
                    nums[n] = std::stoi(s);
                    s = "";
                    n++;
                    continue;
                } else
                    s += c;
            //Cast final value to int (not covered by above loop)
            nums[3] = std::stoi(s);

            //Check if boundaries of one set lie entirely within the other
            if ((nums[2] >= nums[0] && nums[3] <= nums[1]) || (nums[2] <= nums[0] && nums[3] >= nums[1]))
                totalOverlaps++;

            //Check if either boundary of second sit lies within the first, or encloses the first entirely
            if((nums[2] >= nums [0] && nums[2] <= nums[1]) || (nums[3] >= nums [0] && nums[3] <= nums[1]) || (nums[2] < nums[0] && nums[3] > nums[1]))
                partialOverlaps++;
        }
    }
    std::cout << "The number of total overlaps is " << totalOverlaps << " and the number of partial overlaps is " << partialOverlaps;
}