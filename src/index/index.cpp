
#include "index.h"

const int SIZE_ID_STR = 9; // 4294967295
const unsigned long int SIZE_NAME = 10; // unsigned long to work with min(token.length(), ...) below
const unsigned long int SIZE_BIO = 500; // unsigned long to work with min(token.length(), ...) below
const int SIZE_MID_STR = 9; // 4294967295
const int SIZE_RECORD_STR = SIZE_ID_STR + SIZE_NAME + SIZE_BIO + SIZE_MID_STR + 4; // Include commas and newline char

struct Record
{
  unsigned long int id;
  char name[SIZE_NAME];
  char bio[SIZE_BIO];
  unsigned long int mid;
};

const int SIZE_RECORD = sizeof(Record);

Record parse_line(const std::string record_str)
{

  std::istringstream record_steam(record_str);
  std::string token;
  Record rec;

  for (int i = 0; i < 4; i++)
  {
    std::getline(record_steam, token, ',');
    switch (i)
    {
    case 0:
      rec.id = std::stoi(token);
      break;
    case 1:
      token.copy(rec.name, SIZE_NAME, 0);
      rec.name[std::min(token.length(), SIZE_NAME-1)] = 0; // End the string
      break;
    case 2:
      token.copy(rec.bio, SIZE_BIO, 0);
      rec.bio[std::min(token.length(), SIZE_BIO-1)] = 0;  // End the string
      break;
    case 3:
      rec.mid = std::stoi(token);
      break;

    default:
      break;
    }
  }

  std::cout << rec.id << ", " << rec.name << ", " << rec.mid << std::endl;
  return rec;
}

long int get_line(std::FILE *file, long int line_start, std::string &s_buffer)
{
  char b;
  char *c_buffer = (char *)malloc(SIZE_RECORD + 1); // Include space for null char at end
  long int new_line;

  std::fseek(file, 0, line_start);

  for (int i = 0; i < SIZE_RECORD; i++)
  {
    b = std::fgetc(file);
    c_buffer[i] = b;
    //std::cout << b;
    if (b == EOF || b == '\n')
    {
      new_line = std::ftell(file);
      // std::cout << std::endl << "New line: " << new_line << std::endl;
      c_buffer[i + 1] = 0;
      break;
    }
  }
  //std::cout << c_buffer << std::endl;
  s_buffer = c_buffer;
  free(c_buffer);
  return new_line;
}

void create_index(const char *database, const char *index)
{
  long int f_pos = 0;
  long int f_next = 0;
  std::cout << "Building index..." << std::endl;

  std::FILE *db = std::fopen(database, "r");
  if (db == NULL)
  {
    std::cout << "Records file does not exist" << std::endl;
    return;
  }
  std::cout << "Records opened successfully." << std::endl;

  std::vector<Record> employees;
  Record record;

  std::string record_str;

  do
  {
    f_pos = f_next;
    f_next = get_line(db, f_pos, record_str);
    if (f_pos != f_next)
      record = parse_line(record_str);
  } while (f_pos != f_next);

  return;
}