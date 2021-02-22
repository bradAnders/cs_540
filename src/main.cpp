
#include "main.h"


int main(int argc, char **args)
{
  unsigned long long id;
  std::string buffer;
  char *endptr;

  if (argc <= 1)             throw std::invalid_argument("No arguments provided");
  if (args[1][0] != '-')     throw std::invalid_argument("Arguments must start with '-'");

  switch (args[1][1])
  {

  // Index creation
  case 'C':

    if (argc != 2)            throw std::invalid_argument("No extra argments accepted");

    create_index(F_IMPORT, F_INDEX);
    break;

  // ID lookup
  case 'L':

    if (argc != 3)             throw std::invalid_argument("ID expected after -L");
    if (!is_pos_int(args[2]))  throw std::invalid_argument("ID must be a positive integer");
    if (strlen(args[2]) >= 20) throw std::invalid_argument("ID string is too long");
    id = strtoull(args[2], &endptr, 10);
    if (id > 4294967295)       throw std::invalid_argument("ID max size is 8 bytes");
    if (id <= 0)               throw std::invalid_argument("ID must be a positive integer");

    lookup_id(F_INDEX, id);
    break;

  //
  default:
    throw std::invalid_argument("Unrecognized switch");
  }

  return 0;
}

void create_index(const char *import_file, const char *index_file)
{
  Parser csv_read(import_file);
  Database database(index_file, 10);

  while (csv_read.more_records())
    database.add_record(csv_read.next_record());
}

void lookup_id(const char *index, int id) {
  ;
}

bool is_pos_int(const char *buffer)
{
  int i = 0;
  char c;
  bool is_int = true;

  // Zero-length string
  if (buffer[0] == 0)
    return false;

  while (is_int)
  {

    // Overflow
    if (i < 0)
      is_int = false;

    c = buffer[i];

    // End of string, did not see a non-int char
    if (c == 0)
      break;

    // Not a digit character -> not an int string
    if (!isdigit(c))
      is_int = false;

    i++;
  }
  return is_int;
}
