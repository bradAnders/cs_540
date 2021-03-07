
#include "dept.h"


// Grab a single block from the dept.csv file, in theory if a block was larger than
// one tuple, this function would return an array of DeptBlocks and the entire if
// and else statement would be wrapped in a loop for x times based on block size
DeptBlock grabDept(std::fstream &deptin) {
    std::string line, word;
    DeptBlock dept;
    if (std::getline(deptin, line, '\n')) {
        std::stringstream s(line);
        std::getline(s, word,',');
        dept.did = stoi(word);
        std::getline(s, word, ',');
        dept.dname = word;
        std::getline(s, word, ',');
        dept.budget = stod(word);
        std::getline(s, word, ',');
        dept.managerid = stoi(word);
        return dept;
    } else {
        dept.did = -1;
        return dept;
    }
}