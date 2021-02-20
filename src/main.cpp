
#include "main.h"


int main(int argc, char **args) {
  unsigned long long id;
  std::string buffer;
  char* end;
  std::cout << argc << std::endl;

  if (argc <= 1)
    return raise("No arguments provided");

  if (args[1][0] != '-')
    return raise("Arguments must start with '-'");

  switch (args[1][1]) {

    // Index creation
    case 'C':
      
      if (argc != 2)
        return raise("No extra argments accepted");

      create_index(F_DATABASE, F_INDEX);
      break;

    // ID lookup
    case 'L':
      
      // No id provided
      if (argc != 3)
        return raise("ID expected after -L");
      
      // Id is not an int
      if (!is_pos_int(args[2]))
        return raise("ID must be a positive integer");

      // Id is too long to be parsed
      if (strlen(args[2]) >= 20)
        return raise("ID string is too long");

      // Id is too big
      id = strtoull(args[2], &end, 10); 
      if (id > 4294967295)
        return raise("ID max size is 8 bytes");

      // 
      if (id <= 0)
        return raise("ID must be a positive integer");

      lookup_id(F_DATABASE, F_INDEX, id);
      break;

    // 
    default:
      return raise("Unrecognized switch");
  }

  return 0;
}

int raise(const char *message) {
  std::cout << message << std::endl;
  std::cout << "Valid arguments: '-C' for index creation or '-L [id]' for id lookup" << std::endl;
  return 1;
}

bool is_pos_int(const char* buffer) {
  int i = 0;
  char c;
  bool is_int = true;

  // Zero-length string
  if (buffer[0] == 0)
    return false;

  while (is_int) {

    // Overflow
    if (i < 0)
      is_int = false;

    c = buffer[i];

    // End of string, did not see a non-int char
    if (c==0)
      break;

    // Not a digit character -> not an int string
    if (!isdigit(c))
      is_int = false; 
    
    i++;
  }
  return is_int;
}
