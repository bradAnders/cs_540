
#ifndef H_DATABASE
#define H_DATABASE

#include <cmath>     // ceil, log2, pow
#include <cstring>   // strcpy

#include "../record/record.h"

struct Bucket {
  long int target_hash;
  long int file_pos;
  int num_linked;
  double capacity;
};

class Database
{

public:
  Database(const char* index_file, int intial_bucket_count);
  ~Database();

  void add_record(Record);

private:
  int num_buckets;
  Bucket* buckets;
  char *index_file;

  long int hash(long int key);
  int num_lsb();
  int flip_bit(int bucket_id);
  int bucket_id(long int key);
  int avg_bucket_capacity();
};

#endif
