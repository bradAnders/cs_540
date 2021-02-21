
#ifndef H_MAIN
#define H_MAIN

// Built in libraries
#include <iostream>
#include <ctype.h>
#include <string.h>

// Custom libraries
#include "index/index.h"
#include "lookup/lookup.h"

const char *F_DATABASE = "Employee.csv";
const char *F_INDEX = "EmployeeIndex";

int raise(const char *message);
bool is_pos_int(const char *buffer);

#endif
