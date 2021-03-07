#include "emp.h"

// Grab a single block from the emp.csv file, in theorhy if a block was larger than
// one tuple, this function would return an array of EmpBlocks and the entire if
// and else statement would be wrapped in a loop for x times based on block size
EmpBlock grabEmp(std::fstream &empin) {
    std::string line, word;
    EmpBlock emp;
    // grab entire line
    if (std::getline(empin, line, '\n')) {
        // turn line into a stream
        std::stringstream s(line);
        // gets everything in stream up to comma
        std::getline(s, word,',');
        emp.eid = stoi(word);
        std::getline(s, word, ',');
        emp.ename = word;
        std::getline(s, word, ',');
        emp.age = stoi(word);
        std::getline(s, word, ',');
        emp.salary = stod(word);
        return emp;
    } else {
        emp.eid = -1;
        return emp;
    }
}