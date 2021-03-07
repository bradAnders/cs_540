
#ifndef H_EMP
#define H_EMP

// Built in libraries
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct EmpBlock {
    int eid;
    std::string ename;
    int age;
    double salary;
};

EmpBlock grabEmp(std::fstream &empin);

#endif
