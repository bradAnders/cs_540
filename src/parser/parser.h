
#ifndef H_PARSER
#define H_PARSER

// Built in libraries
#include <iostream>  // cout / cin
#include <fstream>   // FILE
#include <sstream>   // Record string
#include <algorithm> // std::min
#include <string>    // string
#include <cstring>   // strcpy
#include <stdexcept> // throw invalid_argument

#include "../record/record.h"

#define BUFFER_SIZE 4000

/**
 * Parses a .CSV file into records
 */
class Parser
{

public:
  Parser(const char *input_filename);
  ~Parser();

  Record next_record(); // TODO - Vectorize this
  Record parse_line(const std::string record_str); // TODO - Vectorize this
  bool more_records();

private:
  std::FILE *input_file;
  char* input_filename;
  long int f_pos;
  long int f_next;
  char* line_buffer;
  std::string next_line();
};

#endif
