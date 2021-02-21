
#include "index.h"

const int SIZE_ID_STR = 9;                                                         // 4294967295
const unsigned long int SIZE_NAME = 200;                                           // unsigned long to work with min(token.length(), ...) below
const unsigned long int SIZE_BIO = 500;                                            // unsigned long to work with min(token.length(), ...) below
const int SIZE_MID_STR = 9;                                                        // 4294967295
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
    if (token.length() <= 1)
      break;

    try
    {
      switch (i)
      {
      case 0:
        rec.id = std::stoi(token);
        break;

      case 1:
        token.copy(rec.name, SIZE_NAME - 1, 0);
        rec.name[std::min(token.length(), SIZE_NAME - 1)] = 0; // End the string
        break;

      case 2:
        token.copy(rec.bio, SIZE_BIO - 1, 0);
        rec.bio[std::min(token.length(), SIZE_BIO - 1)] = 0; // End the string
        break;

      case 3:
        rec.mid = std::stoi(token);
        break;

      default:
        break;
      }
    }
    catch (std::invalid_argument)
    {
      std::cout << "Unable to convert to id: " << token << std::endl;
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

long int get_hash(long int key, int num_buckets) {
  long int raw_hash = key;
  raw_hash ^= raw_hash >> 33;
  raw_hash *= 0xff51afd7ed558ccd;
  raw_hash ^= raw_hash >> 33;
  raw_hash *= 0xc4ceb9fe1a85ec53;
  raw_hash ^= raw_hash >> 33;
  raw_hash = raw_hash % num_buckets;
  return raw_hash;
}

int get_num_lsb(int num_buckets) {
  return int(ceil(log2(num_buckets)));
}

int flip_bit(int bucked_id, int num_lsb) {
  return bucked_id ^ (1 << (num_lsb-1));
}

void create_index(const char *database, const char *index)
{
  long int f_pos = 0;
  long int f_next = 0;
  long int raw_id;
  long int bucket_id;
  int num_buckets = 12;
  int num_raw;
  int num_lsb;
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

  num_lsb = get_num_lsb(num_buckets);
  num_raw = pow(2, num_lsb);
  std::cout << "buckets: " << num_buckets << " , num_lsb: " << num_lsb << ", num_raw: " << num_raw << std::endl;

  do
  {
    f_pos = f_next;
    f_next = get_line(db, f_pos, record_str);
    if (f_pos != f_next) {
      record = parse_line(record_str);
      num_lsb = get_num_lsb(num_buckets);
      raw_id = get_hash(record.id, num_raw);

      if (raw_id >= num_buckets)
        bucket_id = flip_bit(raw_id, num_lsb);
      else
        bucket_id = raw_id;

      std::cout << "bucket: " << bucket_id << " (" << raw_id << ")" << std::endl;
    }

  } while (f_pos != f_next);

  return;
}