
#include "index.h"

struct Record
{
  int id;
  std::string name;
  std::string bio;
  int mid;
};

const int SIZE_ID = 8;
const int SIZE_NAME = 200;
const int SIZE_BIO = 500;
const int SIZE_MID = 8;
const int SIZE_RECORD = SIZE_ID + SIZE_NAME + SIZE_BIO + SIZE_MID + 4; // Include commas and newline char

Record parse_line(const std::string record_str) {
    
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
        rec.name = token;
        break;
      case 2:
        rec.bio = token;
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

long int get_line(std::FILE* file, long int line_start, std::string &s_buffer) {
  char b;
  char *c_buffer = (char*) malloc (SIZE_RECORD+1); // Include space for null char at end
  long int new_line;

  std::fseek(file, 0, line_start);

  for (int i = 0; i < SIZE_RECORD; i++) {
    b = std::fgetc(file);
    c_buffer[i] = b;
    //std::cout << b;
    if (b == EOF || b == '\n') {
      new_line = std::ftell(file);
      // std::cout << std::endl << "New line: " << new_line << std::endl;
      c_buffer[i + 1] = 0;
      break;
    }
  }
  //std::cout << c_buffer << std::endl;
  s_buffer = c_buffer;
  return new_line;
}

void create_index(const char *database, const char *index)
{
  long int f_pos = 0;
  long int f_next = 0;
  std::cout << "Building index..." << std::endl;

  // std::ifstream db(database);
  std::FILE *db = std::fopen(database, "r");
  // if (!db.is_open())
  if (db == NULL)
  { 
    std::cout << "Records file does not exist" << std::endl;
    return;
  }
  std::cout << "Records opened successfully." << std::endl;

  std::vector<Record> employees;
  Record record;

  std::string record_str;

  do {
    f_pos = f_next;
    f_next = get_line(db, f_pos, record_str);
    if (f_pos != f_next)
      record = parse_line(record_str);
    //std::cout << record_str << std::endl;
  } while (f_pos != f_next);

    return;
}