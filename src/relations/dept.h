
#ifndef H_DEPT
#define H_DEPT

// Built in libraries
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct DeptBlock {
    int did;
    std::string dname;
    double budget;
    int managerid;
};

DeptBlock grabDept(std::fstream &deptin);

#endif
