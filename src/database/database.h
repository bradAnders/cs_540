
#ifndef H_DATABASE
#define H_DATABASE

#include <fstream>   // FILE
#include <cmath>     // ceil, log2, pow
#include <string>    // std::to_string
#include <cstring>   // strcpy
#include <sstream>   // Record string
#include <stdexcept> // throw invalid_argument

#include "../record/record.h"
#include "../parser/parser.h"
#define BLOCK_SIZE 4000


struct Bucket {
  long int target_hash;
  long int file_pos;
  int num_linked;
  double capacity;
};

struct Block {
  long int block_id;
  long int next;
  int num_records;
  Record *records;
};

class Database
{

public:
  Database(const char* index_file, int intial_bucket_count);
  ~Database();

  void add_record(Record);

private:
  std::FILE *index_file;
  char* index_filename;

  int num_buckets;
  Bucket* buckets;

  void initialize_index(int intial_bucket_count);
  void read_from_index(void);
  char *get_header(void);

  Block parse_block(char *read_buffer);

  long int hash(long int key);
  int num_lsb();
  int flip_bit(int bucket_id);
  int bucket_id(long int key);
  int avg_bucket_capacity();
};

#endif
