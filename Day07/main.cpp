#include <iostream>
#include <fstream>
#include <map>

//#define logging

int main() {
    std::string cwd = "/"; //CURRENT WORKING DIRECTORY
    std::fstream input("Day07/input.txt");
    std::map<std::string,int> directories; //MAP TO HOLD DIRECTORY SIZES

    if (input.is_open()) {
        std::string line;
        bool cont = (bool) std::getline(input, line); //CONTROL THE WHILE LOOP
        while (cont) {
            //LINE IS COMMANDS
            if (line[0] == '$') {
#ifdef logging
                std::cout << "user:" << cwd << " $ "; //AESTHETICS
#endif
                //CD COMMAND
                if (line[2] == 'c') {
#ifdef logging
                    std::cout << "cd ";
#endif
                    //CHANGE TO ROOT DIRECTORY
                    if (line[5] == '/') {
                        cwd = "/";
#ifdef logging
                        std::cout << "/" << std::endl;
#endif
                    }
                        //OPEN PARENT FOLDER
                    else if (line[5] == '.') {
#ifdef logging
                        std::cout << ".." << std::endl;
#endif
                        if (cwd.size() == 1) {
                            std::cout << "Error: cannot .. in root directory" << std::endl; //SHOULD NEVER HAPPEN
                            return 1;
                        }
                        //TRIM DEEPEST FOLDER FROM WORKING DIRECTORY
                        while (cwd[cwd.size() - 1] != '/')
                            cwd.pop_back();
                        //TRIM THE /, UNLESS ROOT DIR
                        if (cwd.size() > 1)
                            cwd.pop_back();
                    }
                        //OPEN FOLDER
                    else {
                        //ADD THE / BEFORE THE NEW FOLDER IN CWD (NOT NEEDED IN ROOT)
                        if (cwd.size() > 1)
                            cwd.push_back('/');
                        //EXTRACT FOLDERNAME FROM INPUT LINE
                        std::string fileName;
                        for (int i = 5; i < line.size(); i++) {
                            fileName.push_back(line[i]);
                            cwd.push_back(line[i]);
                        }
#ifdef logging
                        std::cout << fileName << std::endl; //AESTHETICS
#endif
                    }
                }
                    //LS COMMAND
                else {
#ifdef logging
                    std::cout << "ls" << std::endl;
#endif
                }
                cont = (bool) std::getline(input, line);
            }
            //LINE IS DIRECTORY CONTENTS
            while (line[0] != '$' && cont) {
                //LINE IS A DIRECTORY
                if (line[0] == 'd') {
#ifdef logging
                    std::cout << "dir ";
#endif
                    std::string folderName;
                    //GET DIRECTORY NAME FROM INPUT LINE
                    for (int i = 4; i < line.size(); i++) {
#ifdef logging
                        std::cout << line[i];
#endif
                        folderName.push_back(line[i]);
                    }
#ifdef logging
                    std::cout << std::endl;
#endif
                }
                //LINE IS A FILE
                else {
                    std::string fileSize;
                    std::string fileName;
                    //GET FILESIZE FROM LINE INPUT
                    int n = 0;
                    while (line[n] != ' ')
                        fileSize.push_back(line[n++]);
                    n++; //IGNORE SPACE ' '
                    //GET FILENAME FROM INPUT
                    while (n < line.size())
                        fileName.push_back(line[n++]);
#ifdef logging
                    std::cout << fileSize << " " << fileName << std::endl;
#endif
                    //ADD FILESIZE TO ALL PARENT DIRS
                    std::string dir = cwd;
                    //ADD FILESIZE FOR CWD. NOT NEEDED FOR ROOT SINCE COVERED IN WHILE LOOP
                    if(dir.size() > 1)
                        directories[dir] += std::stoi(fileSize);
                    while (true) {
                        //HANDLE ROOT DIR CASE
                        if (dir.size() == 1) {
                            directories["/"] += std::stoi(fileSize);
                            break;
                        }
                        //ALL OTHER DIRS
                        else if (dir[dir.size() - 1] == '/') {
                            dir.pop_back();
                            directories[dir] += std::stoi(fileSize);
                        }
                        dir.pop_back();
                    }
                }
                //CHECK IF MORE LINES TO PROCESS
                cont = (bool)std::getline(input, line);
            }
        }
    }

    //PRINT ALL DIRECTORY VALUES AND FIND IMPORTANT VALUES
    int totalLargeDirs = 0;
    int smallestLargeDir = directories["/"];
    int spaceRequired = 30000000 - (70000000 - smallestLargeDir);
    for (auto i : directories) {
        if (i.second < 100000 && i.first != "/")
            totalLargeDirs += i.second;
        if (i.second > spaceRequired && i.second < smallestLargeDir)
            smallestLargeDir = i.second;
#ifdef logging
        std::cout << std::endl << "Directory " << i.first << " size is " << i.second;
#endif
    }
#ifdef logging
    std::cout << std::endl << std::endl;
#endif
    std::cout << "Total size of directories greater than 10,000 is: " << totalLargeDirs;
    std::cout << std::endl << "The smallest dir with size larger than 30,000,000 is: " << smallestLargeDir;

    return 0;
}
