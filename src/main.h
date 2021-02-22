
#ifndef H_MAIN
#define H_MAIN

// Built in libraries
#include <iostream>
#include <ctype.h>
#include <string.h>

// Custom libraries
#include "parser/parser.h"
#include "record/record.h"
#include "database/database.h"

const char *F_IMPORT = "Employee.csv";
const char *F_INDEX = "EmployeeIndex";

int raise(const char *message);
bool is_pos_int(const char *buffer);
void create_index(const char *database, const char *index);
void lookup_id(const char *index, int id);

#endif
