
#include "index.h"
#include "../parser/parser.h"
#include "../record/record.h"


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
  long int raw_id;
  long int bucket_id;
  int num_buckets = 12;
  int num_raw;
  int num_lsb;
  std::cout << "Building index..." << std::endl;

  Parser csv_read (database);

  Record record;

  num_lsb = get_num_lsb(num_buckets);
  num_raw = pow(2, num_lsb);
  std::cout << "buckets: " << num_buckets << " , num_lsb: " << num_lsb << ", num_raw: " << num_raw << std::endl;

  //do
  while(csv_read.more_records())
  {
    record = csv_read.next_record();
    num_lsb = get_num_lsb(num_buckets);
    raw_id = get_hash(record.id, num_raw);

    if (raw_id >= num_buckets)
      bucket_id = flip_bit(raw_id, num_lsb);
    else
      bucket_id = raw_id;

    std::cout << "bucket: " << bucket_id << " (" << raw_id << ")" << std::endl;

  }

  return;
}